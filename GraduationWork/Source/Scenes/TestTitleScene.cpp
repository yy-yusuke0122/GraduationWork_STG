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
	// 「1」キーの入力を受けたらメインシーンへ移動
	if (Input::IsKeyDown(KEY::KEY_1)) {
		SceneManager::isAsyncLoad = true;
		SceneManager::LoadScene<TestMainScene>();
	}
	if (Input::IsKeyPush(KEY::KEY_ESCAPE))
		SceneManager::End();
}
