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
	//Quake quake;
	//quake.time = 10;
	//quake.Play();
	//quake.Update();
	float* a;
	float b;
	a = &b;
	VECTOR2* p = &Scroll::quake.center;
	*p = VECTOR2::one();
	Scroll::quake.a = 100;
	Scroll::value.x = 10.f;
	Scroll::quake.center.x = 50.f;
	Scroll::quake.center.y = 50.f;
	Scroll::quake.speed.x = 10000.f;
	Scroll::quake.speed.y = 10000.f;
	Scroll::quake.scale.x = 500.f;
	Scroll::quake.scale.y = 500.f;
	Scroll::quake.time = 10.f;
	Scroll::quake.Update();

	//	Scroll::isUseDeltaTime = true;

	Scroll::quake.Play();
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

	int x, y;
	map->GetColliderSize(empty, &x, &y);

	if (Input::IsKeyPush(KEY::KEY_Z))--Scroll::speed.x;
	if (Input::IsKeyPush(KEY::KEY_X))++Scroll::speed.x;
	if (Input::IsKeyPush(KEY::KEY_C))--Scroll::speed.y;
	if (Input::IsKeyPush(KEY::KEY_V))++Scroll::speed.y;
	map->SetColliderSize(empty, &x, &y);

	printfDx("x : %d, y : %d\n", x, y);

//	DEBUG_LOG("hogehoge");

	if (Input::IsKeyDown(KEY::KEY_ENTER))
		Scroll::isUseDeltaTime = !Scroll::isUseDeltaTime;

	InputInfo info = Input::GetInfo("X");

	printfDx("\nX↓↓\n");
	printfDx("accele : %f\n", info.accele);
	printfDx("dead	 : %f\n", info.dead);
	printfDx("speed	 : %f\n", info.speed);
	printfDx("value	 : %f\n", info.value);
	printfDx("weak	 : %f\n", info.weak);
	printfDx("isSnap : %d\n", info.isSnap);

	info = Input::GetInfo("Y");
	printfDx("\nY↓↓\n");
	printfDx("accele : %f\n", info.accele);
	printfDx("dead	 : %f\n", info.dead);
	printfDx("speed	 : %f\n", info.speed);
	printfDx("value	 : %f\n", info.value);
	printfDx("weak	 : %f\n", info.weak);
	printfDx("isSnap : %d\n", info.isSnap);

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
