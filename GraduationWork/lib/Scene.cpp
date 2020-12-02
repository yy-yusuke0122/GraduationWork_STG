#include "dxlib/DxLib.h"
#include "Scene.h"
#include "AsyncComponent.h"
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

	//�T�u�V�[���j��
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

	//���g�̃I�u�W�F�N�g�̃R���|�[�l���g�j��
	for (std::list<GameObject*>::iterator it = objectList.begin(); it != objectList.end(); ++it)
	{
		(*it)->DestroyComponents();
	}

	//�񓯊��ǂݍ��݂��I�����������`�F�b�N
	for (std::list<AsyncComponent*>::iterator it = asyncList.begin(); it != asyncList.end();)
	{
		if ((*it)->CheckAsync())
		{
			++it;
		}
		else
		{
			(*it)->Initialize();
			
			if (asyncScene == nullptr)
			{
				(*it)->AsyncEnd();
				(*it)->gameObject->AsyncEnd();
			}
			else
				asyncWaitList.emplace_back(*it);

			it = asyncList.erase(it);
		}
	}

	//�񓯊��ǂݍ��ݒ��܂��͔񓯊��V�[�����Ԃ��c���Ă���
	bool isTimeRemain = asyncTime > 0.f;
	bool isasync = (isTimeRemain) || (GetAsyncLoadCountWithSubScene() > 0);
	if (isasync)
	{
		//�񓯊��V�[������
		if (asyncScene == nullptr && asyncNode.createScene != nullptr)
		{
			asyncScene = asyncNode.createScene();
			asyncScene->SetName(asyncNode.name);
			asyncTime = asyncUseTime;
			
			asyncScene->SetActive(false);
			asyncScene->SceneStart();
			asyncScene->parentScene = this;
		}
		else
		{
			if (isTimeRemain)
				asyncTime -= Time::DeltaTime();
		}
	}
	else
	{
		//�񓯊��V�[���j��
		if (asyncScene != nullptr && !asyncScene->IsActive())//�A�N�e�B�u�Ŕ���
		{
			delete asyncScene;
			asyncScene = nullptr;

			for (std::list<AsyncComponent*>::iterator it = asyncWaitList.begin(); it != asyncWaitList.end();)
			{
				(*it)->AsyncEnd();
				(*it)->gameObject->AsyncEnd();
				it = asyncWaitList.erase(it);
			}
		}
		asyncTime = 0.f;
	}

	if (isAsyncLoad)
		SetUseASyncLoadFlag(TRUE);

	//�T�u�V�[���ēǂݍ���
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

	//�T�u�V�[���̒ǉ�
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
		//�񓯊��V�[���X�V
		asyncScene->SceneUpdate();
	}
	else
	{
		//�T�u�V�[���̍X�V
		for (std::list<Scene*>::iterator it = subSceneList.begin(); it != subSceneList.end(); ++it)
		{
			if ((*it)->IsActive())
			{
				(*it)->SceneUpdate();
			}
		}

		currentScene = this;

		//���g�̃I�u�W�F�N�g�X�V
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

GameObject* Scene::FindGameObject(const std::string& _tag)
{
	for (std::list<GameObject*>::iterator it = objectList.begin(), end = objectList.end(); it != end; ++it)
		if ((*it)->tag == _tag)
			return *it;
	return nullptr;
}

int Scene::GetAsyncLoadCount()const
{
	return static_cast<int>(asyncList.size());
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

void Scene::AddAsync(AsyncComponent* _async)
{
	asyncList.emplace_back(_async);
}

void Scene::EraseAsync(AsyncComponent* _async)
{
	for (std::list<AsyncComponent*>::iterator it = asyncList.begin(), end = asyncList.end(); it != end; ++it)
	{
		if ((*it) == _async)
		{
			asyncList.erase(it);
			break;
		}
	}
}

void Scene::DestroyGameObjects()
{
	//�e�̎��S�t���O�������Ă���ꍇ�A�q�̎��S�t���O�𗧂Ă�
	for (std::list<GameObject*>::iterator it = objectList.begin(), end = objectList.end(); it != end; ++it)
	{
		if (!(*it)->IsDestroy())continue;

		std::list<GameObject*> children = (*it)->GetChildren();
		for (std::list<GameObject*>::iterator cit = children.begin(), cend = children.end(); cit != cend; ++cit)
		{
			(*it)->Destroy();
		}
	}
	
	//�T�u�V�[���`�F�b�N
	for (std::list<Scene*>::iterator it = subSceneList.begin(), end = subSceneList.end(); it != end; ++it)
		(*it)->DestroyGameObjects();

	//���g�̃I�u�W�F�N�g�j��
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
