#include "MainScene.h"
#include "TitleScene.h"
#include "../Objects/Player.h"
#include "../Objects/Enemy.h"
#include "../Components/Life.h"

MainScene::MainScene()
{
	player = Instantiate<Player>();
	enemy = Instantiate<Enemy>();
}

MainScene::~MainScene()
{
}

void MainScene::Start()
{
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

	printfDx("PlayerHP : %2.f\n", player->GetComponent<Life>()->hp);

	printfDx("MainScene\n");
	printfDx("Press '0' : To 'TitleScene'\n");
}

void MainScene::CheckInput()
{
	// 「0」キーの入力を受けたらメインシーンへ移動
	if (Input::IsKeyDown(KEY::KEY_0)) {
		SceneManager::Get()->LoadScene<TitleScene>();
	}
}
