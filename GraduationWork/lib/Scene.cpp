#include "dxlib/DxLib.h"
#include "Scene.h"
#include "Renderer.h"
#include "Sound.h"
#include "Time.h"

Scene* Scene::currentScene = nullptr;

Scene::~Scene()
{
	for (std::list<GameObject*>::iterator it = objectList.begin(); it != objectList.end(); ++it)
	{
		(*it)->Destroy();
	}
	DestroyGameObjects();

	for (std::list<Scene*>::iterator it = subSceneList.begin(); it != subSceneList.end();)
	{
		delete* it;
		it = subSceneList.erase(it);
	}
	addSceneList.clear();

	if (asyncScene != nullptr)
	{
		delete asyncScene;
		asyncScene = nullptr;
	}
}

void Scene::SceneStart()
{
	Start();
}

void Scene::SceneUpdate()
{
	DestroyGameObjects();

	//サブシーン破棄
	for (std::list<Scene*>::iterator it = subSceneList.begin(); it != subSceneList.end();)
	{
		if ((*it)->IsDestroy())
		{
			delete* it;
			it = subSceneList.erase(it);
		}
		else
			++it;
	}

	//自身のオブジェクトのコンポーネント破棄
	for (std::list<GameObject*>::iterator it = objectList.begin(); it != objectList.end(); ++it)
	{
		(*it)->DestroyComponents();
	}

	//レンダラーの非同期読み込みが終了したかをチェック
	for (std::list<Renderer*>::iterator it = asyncRendererList.begin(); it != asyncRendererList.end();)
	{
		if ((*it)->CheckAsync())
		{
			++it;
		}
		else
		{
			(*it)->Initialize();
			it = asyncRendererList.erase(it);
		}
	}

	//サウンドの非同期読み込みが終了したかをチェック
	for (std::list<Sound*>::iterator it = asyncSoundList.begin(); it != asyncSoundList.end();)
	{
		if ((*it)->CheckAsync())
		{
			++it;
		}
		else
		{
			it = asyncSoundList.erase(it);
		}
	}

	//非同期読み込み中または非同期シーン時間が残っている
	bool isTimeRemain = asyncTime > 0.f;
	bool isasync = (GetAsyncLoadCountWithSubScene() > 0) || (isTimeRemain);
	if (isasync)
	{
		//非同期シーン生成
		if (asyncScene == nullptr && asyncNode.createScene != nullptr)
		{
			asyncScene = asyncNode.createScene();
			asyncScene->SetName(asyncNode.name);
			asyncTime = asyncUseTime;
		}
		else
		{
			if (isTimeRemain)
				asyncTime -= Time::DeltaTime();
		}
	}
	else
	{
		//非同期シーン破棄
		if (asyncScene != nullptr)
		{
			delete asyncScene;
			asyncScene = nullptr;
		}
		asyncTime = 0.f;
	}

	if (isAsyncLoad)
		SetUseASyncLoadFlag(TRUE);

	//サブシーン再読み込み
	for (std::list<Scene*>::iterator it = subSceneList.begin(), end = subSceneList.end(); it != end; ++it)
	{
		if ((*it)->IsReload())
		{
			std::string name = (*it)->GetTypeName();
			Scene* (*f)() = (*it)->reloadScene;
			delete* it;
			*it = f();
			(*it)->SetName(name);
			(*it)->reloadScene = f;
			(*it)->parentScene = this;
			(*it)->SceneStart();
		}
	}

	//サブシーンの追加
	for (std::list<NODE>::iterator it = addSceneList.begin(); it != addSceneList.end();)
	{
		Scene* p = it->createScene();
		p->SetName(it->name);
		p->reloadScene = it->createScene;
		p->parentScene = this;
		p->SceneStart();
		subSceneList.emplace_back(p);
		it = addSceneList.erase(it);
	}

	SetUseASyncLoadFlag(FALSE);

	if (isasync && asyncScene != nullptr)
	{
		//非同期シーン更新
		asyncScene->SceneUpdate();
	}
	else
	{
		//サブシーンの更新
		for (std::list<Scene*>::iterator it = subSceneList.begin(); it != subSceneList.end(); ++it)
		{
			if ((*it)->IsActive())
			{
				(*it)->SceneUpdate();
			}
		}

		currentScene = this;

		//自身のオブジェクト更新
		for (std::list<GameObject*>::iterator it = objectList.begin(); it != objectList.end(); ++it)
		{
			if ((*it)->IsActive())
			{
				(*it)->Update();
			}
		}

		Update();
	}

	currentScene = nullptr;
}

int Scene::GetSubSceneCount() const
{
	return static_cast<int>(subSceneList.size());
}

int Scene::GetAsyncLoadCount()const
{
	return static_cast<int>(asyncRendererList.size());
}

int Scene::GetAsyncLoadCountWithSubScene()const
{
	int sum = 0;

	for (std::list<Scene*>::const_iterator it = subSceneList.begin(), end = subSceneList.end(); it != end; ++it)
		sum += (*it)->GetAsyncLoadCountWithSubScene();

	return sum + GetAsyncLoadCount();
}

bool Scene::AddGameObject(GameObject* _object)
{
	if (_object == nullptr)return false;

	for (std::list<GameObject*>::iterator it = objectList.begin(), end = objectList.end(); it != end; ++it)
		if (_object == (*it))return false;

	objectList.emplace_back(_object);

	return true;
}

void Scene::AddAsyncRenderer(Renderer* _renderer)
{
	asyncRendererList.emplace_back(_renderer);
}

void Scene::EraseAsyncRenderer(Renderer* _renderer)
{
	for (std::list<Renderer*>::iterator it = asyncRendererList.begin(), end = asyncRendererList.end(); it != end; ++it)
	{
		if ((*it) == _renderer)
		{
			asyncRendererList.erase(it);
			break;
		}
	}
}

void Scene::AddAsyncSound(Sound* _sound)
{
	asyncSoundList.emplace_back(_sound);
}

void Scene::EraseAsyncSound(Sound* _sound)
{
	for (std::list<Sound*>::iterator it = asyncSoundList.begin(), end = asyncSoundList.end(); it != end; ++it)
	{
		if ((*it) == _sound)
		{
			asyncSoundList.erase(it);
			break;
		}
	}
}

void Scene::DestroyGameObjects()
{
	//親の死亡フラグが立っている場合、子の死亡フラグを立てる
	for (std::list<GameObject*>::iterator it = objectList.begin(), end = objectList.end(); it != end; ++it)
	{
		if (!(*it)->IsDestroy())continue;

		std::list<GameObject*> children = (*it)->GetChildren();
		for (std::list<GameObject*>::iterator cit = children.begin(), cend = children.end(); cit != cend; ++cit)
		{
			(*it)->Destroy();
		}
	}
	
	//サブシーンチェック
	for (std::list<Scene*>::iterator it = subSceneList.begin(), end = subSceneList.end(); it != end; ++it)
		(*it)->DestroyGameObjects();

	//自身のオブジェクト破棄
	for (std::list<GameObject*>::iterator it = objectList.begin(); it != objectList.end();)
	{
		if ((*it)->IsDestroy())
		{
			delete* it;
			it = objectList.erase(it);
		}
		else
			++it;
	}
}
