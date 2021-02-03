#include "TestTitleScene.h"
#include "TestMainScene.h"
#include "../Components/TestMapColMover.h"

namespace
{
	constexpr int cs = 32;
}

TestTitleScene::TestTitleScene()
{
	//Scroll::quake.QuakeEndCallback(this, &TestTitleScene::CheckInput);
	//void (Object:: * p)() = Scroll::quake.GetCallBack();
}

TestTitleScene::~TestTitleScene()
{
}

void TestTitleScene::Start()
{
//	UrLib::CollideInit(1,100,100,100,100);

	map = Instantiate<MapChip>();
	map->Create(16, 16, cs, cs);
	for (int h = 0; h < 16; ++h)
		for (int w = 0; w < 16; ++w)
		{
			Chip* chip = map->GetChip(h, w);
			ImageRenderer* p = chip->AddComponent<ImageRenderer>();
			p->SetImage("Media/Player.png");
			chip->type = GetRand(5) == 0;
			if (chip->type)
				p->blue = 0;
		}
	//map->isLoopX = true;
	//map->isLoopY = true;

	empty = Instantiate<GameObject>();
	empty->AddComponent<TMCMover>();
	empty->tag = "gehageha";
	img = empty->AddComponent<ImageRenderer>();
	img->SetImage("Media/Player.png");
	img->blue = img->green = 0;

	map->SetChipCollider(empty);

	//▼▼▼やばい▼▼▼
	//Scroll::value.x = 10.f;
	//Scroll::GetQuake()->center.x = 50.f;
	//Scroll::GetQuake()->center.y = 50.f;
	//Scroll::GetQuake()->speed.x = 10000.f;
	//Scroll::GetQuake()->speed.y = 10000.f;
	//Scroll::GetQuake()->scale.x = 500.f;
	//Scroll::GetQuake()->scale.y = 500.f;
	//Scroll::GetQuake()->time = 10.f;

	//Scroll::GetQuake()->Play();
	//Scroll::GetQuake()->isPlay = true;
	//▲▲▲▲▲▲▲

	dest = Instantiate<GameObject>();
	dest->transform->position.x = 700;
	dest->transform->position.y = 300;

	ImageRenderer* image = dest->AddComponent<ImageRenderer>();
	image->SetImage("Media\\Player.png");
	image->red = image->green = 0;
	map->SetChipCollider(dest);
}

void TestTitleScene::Update()
{
	CheckInput();

	printfDx("TitleScene\n");
	printfDx("Press '1' : To 'MainScene'\n");

	//	DEBUG_LOG("hogehoge");

	int h, w;
	map->FindRoute
	(
		empty->transform->position.y / map->GetSizeY(), empty->transform->position.x / map->GetSizeX(),
		dest->transform->position.y / map->GetSizeY(), dest->transform->position.x / map->GetSizeX(),
		[](int _type) { return !_type; },
		h, w
	);

	ImageRenderer* image = map->GetChip(h, w)->GetComponent<ImageRenderer>();
	image->red = image->blue = 0;

	if(Input::IsKeyDown(KEY::KEY_SPACE))
	for (h = 0; h < map->GetHeight(); ++h)
	{
		for (w = 0; w < map->GetWidth(); ++w)
		{
			ImageRenderer* p = map->GetChip(h, w)->GetComponent<ImageRenderer>();
			p->SetOrder(GetRand(100));
		}
	}

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
