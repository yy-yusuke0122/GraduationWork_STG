#include "dxlib/DxLib.h"
#include "SceneManager.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager* SceneManager::Get()
{
	if (instance == nullptr)
	{
		instance = new SceneManager();
	}
	return instance;
}

SceneManager::~SceneManager()
{
	if (mainScene != nullptr)
	{
		delete mainScene;
		mainScene = nullptr;
	}
}

bool SceneManager::Destroy()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
		return true;
	}
	return false;
}

void SceneManager::Start()
{
}

void SceneManager::Update()
{
	if (createScene != nullptr)
		ChangeScene();

	if (mainScene != nullptr)
	{
		if (mainScene->IsDestroy())
		{
			delete mainScene;
			mainScene = nullptr;
		}
		else
		{
			if (mainScene->IsReload())
			{
				if (isAsyncLoad)
					SetUseASyncLoadFlag(TRUE);

				Scene* (*f)() = mainScene->reloadScene;
				std::string name = mainScene->GetTypeName();
				delete mainScene;
				mainScene = f();
				mainScene->SetName(name);
				mainScene->reloadScene = f;

				SetUseASyncLoadFlag(FALSE);
			}

//			if (mainScene->IsActive())
			{
				mainScene->SceneUpdate();
			}
		}
	}
}

int SceneManager::GetAsyncLoadAllCount()
{
	return 	GetASyncLoadNum();
}

void SceneManager::ChangeScene()
{
	if (mainScene != nullptr)
		delete mainScene;

	if (isAsyncLoad)
		SetUseASyncLoadFlag(TRUE);

	Scene* (*p)() = createScene;

	createScene = nullptr;

	mainScene = p();
	
	mainScene->SetName(sceneName);

	mainScene->reloadScene = p;

	mainScene->SceneStart();

	SetUseASyncLoadFlag(FALSE);

}
