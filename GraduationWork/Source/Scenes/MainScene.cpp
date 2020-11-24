#include "MainScene.h"
#include "TitleScene.h"
#include "../Objects/Player.h"
#include "../Objects/Enemy.h"

MainScene::MainScene()
{
	Instantiate<Player>();
	Instantiate<Enemy>();
}

MainScene::~MainScene()
{
}

void MainScene::Start()
{
}

void MainScene::Update()
{
	CheckInput();

	printfDx("MainScene\n");
	printfDx("Press '0' : To 'TitleScene'\n");
}

void MainScene::CheckInput()
{
	// �u0�v�L�[�̓��͂��󂯂��烁�C���V�[���ֈړ�
	if (Input::IsKeyDown(KEY::KEY_0)) {
		SceneManager::Get()->LoadScene<TitleScene>();
	}
}
