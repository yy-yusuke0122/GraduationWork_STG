#include "TestTitleScene.h"
#include "TestMainScene.h"

TestTitleScene::TestTitleScene()
{
}

TestTitleScene::~TestTitleScene()
{
}

void TestTitleScene::Start()
{
}

void TestTitleScene::Update()
{
	CheckInput();

	printfDx("TitleScene\n");
	printfDx("Press '1' : To 'MainScene'\n");
}

void TestTitleScene::CheckInput()
{
	// �u1�v�L�[�̓��͂��󂯂��烁�C���V�[���ֈړ�
	if (Input::IsKeyDown(KEY::KEY_1)) {
		SceneManager::isAsyncLoad = true;
		SceneManager::LoadScene<TestMainScene>();
	}
	if (Input::IsKeyPush(KEY::KEY_ESCAPE))
		SceneManager::End();
}
