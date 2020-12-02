#include "TitleScene.h"
#include "MainScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Start()
{
}

void TitleScene::Update()
{
	CheckInput();

	printfDx("TitleScene\n");
	printfDx("Press '1' : To 'MainScene'\n");
}

void TitleScene::CheckInput()
{
	// 「1」キーの入力を受けたらメインシーンへ移動
	if (Input::IsKeyDown(KEY::KEY_1)) {
		SceneManager::Get()->isAsyncLoad = true;
		SceneManager::Get()->LoadScene<MainScene>();
	}
	if (Input::IsKeyPush(KEY::KEY_ESCAPE))
		SceneManager::Get()->End();
}
