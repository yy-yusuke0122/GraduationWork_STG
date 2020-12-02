#include "MainScene.h"
#include "TitleScene.h"
#include "LoadingScene.h"
#include "../Objects/Player.h"
#include "../Objects/Enemy.h"
#include "../Components/Life.h"
#include "../Objects/Stage.h"
#include "../Objects/ScreenCollider.h"
#include "../Components/CheckDeadObjects.h"
#include "../Objects/SoundManager.h"

MainScene::MainScene()
{
	asyncMinTime = LoadingScene::asyncLoadMin;
	AsyncScene<LoadingScene>();

}

MainScene::~MainScene()
{
	SoundManager::Destroy();
}

void MainScene::Start()
{
	Instantiate<ScreenCollider>();
	player = Instantiate<Player>();
	enemy = Instantiate<Enemy>();
	Instantiate<Stage>();
	Instantiate<GameObject>()->AddComponent<CheckDeadObjects>();
	SoundManager::Create(this);

	SoundManager::Get()->Push("Sound/BGM.mp3", "MainBGM");

	VECTOR3 center = VGet((float)(Screen::x / 2), (float)(Screen::y / 2), 0.0f);
	VECTOR3 add = VGet(200.0f, 0.0f, 0.0f);
	player->transform->SetPosition(center);
	player->transform->AddPosition(-add);
	enemy->transform->SetPosition(center);
	enemy->transform->AddPosition(add);
}

void MainScene::Update()
{
	CheckInput();

#ifdef _DEBUG

	if (FindGameObject("Player") != nullptr)
		printfDx("PlayerHP : %2.f\n", player->GetComponent<Life>()->hp);
	if (FindGameObject("Enemy") != nullptr)
		printfDx("EnemyHP : %2.f\n", enemy->GetComponent<Life>()->hp);

	printfDx("MainScene\n");
	printfDx("Press '0' : To 'TitleScene'\n");

#endif // !_DEBUG
}

void MainScene::AsyncEnd()
{
	SoundManager::Get()->Play("MainBGM");
}

void MainScene::CheckInput()
{
	// 「0」キーの入力を受けたらメインシーンへ移動
	if (Input::IsKeyDown(KEY::KEY_0)) {
		SceneManager::Get()->LoadScene<TitleScene>();
	}
	if (Input::IsKeyPush(KEY::KEY_ESCAPE))
		SceneManager::Get()->End();
}
