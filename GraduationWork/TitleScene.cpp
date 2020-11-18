#include "TitleScene.h"
#include "TitleSubScene.h"
#include "GameMain.h"
#include "TestTransformScene.h"
#include "AnimTestScene.h"
#include "TestCollisionScene.h"
#include "Player.h"
#include "PlayerRotate.h"
#include "PlayerChanger.h"

TitleScene::TitleScene()
{
	player1 = Instantiate<Player>();
	player2 = Instantiate<Player>();
	player3 = Instantiate<Player>();
	player4 = Instantiate<Player>();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Start()
{
	player1->AddComponent<PlayerRotate>();
	player2->AddComponent<PlayerRotate>();
	player3->AddComponent<PlayerRotate>();
	player4->AddComponent<PlayerRotate>();
	player1->AddComponent<PlayerChanger>();
	player2->AddComponent<PlayerChanger>();
	player2->transform->position.x = static_cast<float>(Screen::x);
	player2->transform->position.y = static_cast<float>(Screen::y);
	player2->GetComponent<PlayerRotate>()->SetRotate(180.0f);
	player3->AddComponent<PlayerChanger>();
	player4->AddComponent<PlayerChanger>();
	player3->transform->position.x = static_cast<float>(Screen::x);
	player4->transform->position.y = static_cast<float>(Screen::y);
	player3->GetComponent<PlayerRotate>()->SetRotate(-90.0f);
	player4->GetComponent<PlayerRotate>()->SetRotate(90.0f);
}

void TitleScene::Update()
{
	printfDx("TitleScene\n");
	if (Input::IsKeyDown(KEY::KEY_ENTER))SceneManager::Get()->LoadScene<GameMain>();
	if (Input::IsKeyDown(KEY::KEY_T))SceneManager::Get()->LoadScene<TestTransformScene>();
	if (Input::IsKeyDown(KEY::KEY_A))SceneManager::Get()->LoadScene<AnimTestScene>();
	if (Input::IsKeyDown(KEY::KEY_C))SceneManager::Get()->LoadScene<TestCollisionScene>();
	if (Input::IsKeyDown(KEY::KEY_S))SceneManager::Get()->AddSubScene<TitleSubScene>();
}
