#include "TitleSubScene.h"
#include "TitleScene.h"
#include "Player.h"
#include "PlayerRotate.h"

TitleSubScene::TitleSubScene() :
	count(0)
{
	player = Instantiate<Player>();
	child = Instantiate<Player>();
}

TitleSubScene::~TitleSubScene()
{
}

void TitleSubScene::Start()
{
	count = 0;
	child->SetParent(player);
	float dif = 200;
	player->transform->position.x = Screen::x / 2.0f - dif;
	player->transform->position.y = Screen::y / 2.0f;
	child->transform->position.x = Screen::x / 2.0f + dif;
	child->transform->position.y = Screen::y / 2.0f;
	child->GetComponent<PlayerRotate>()->SetRotate(180.0f);
	player->GetComponent<ImageRenderer>()->SetImage("..\\Media\\testImage2.png");
	child->GetComponent<ImageRenderer>()->SetImage("..\\Media\\testImage2.png");
}

void TitleSubScene::Update()
{
	printfDx("TitleSubScene\n");
	if (++count > 120) {
		SceneManager::Get()->DestroySubScene<TitleSubScene>();
	}	
}
