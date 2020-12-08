#include "../lib/UrLib.h"
#include "Scenes/TestTitleScene.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (UrLib::Init(800, 900, 32, TRUE) < 0)		// URライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//TODO
	//SceneManager::Get()->isAsyncLoad = true;
	//Loader::isAsync = true;
	//Saver::isAsync = true;

	SceneManager::LoadScene<TestTitleScene>();

	//メイン処理
	UrLib::Update();

	UrLib::End();			// URライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
