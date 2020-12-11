#include "TestTitleScene.h"
#include "TestMainScene.h"
#include "../Components/TestMapColMover.h"

namespace
{
	constexpr int cs = 32;
}

TestTitleScene::TestTitleScene()
{
	Scroll::value.x = -200.f;
	Scroll::value.y = -100.f;
	Scroll::speed.x = 1.f;
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
			ImageRenderer* p = map->GetChip(h, w)->AddComponent<ImageRenderer>();
			p->SetImage("Media/Player.png");
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

}

void TestTitleScene::Update()
{
	CheckInput();

	printfDx("TitleScene\n");
	printfDx("Press '1' : To 'MainScene'\n");

	int x, y;
	map->GetColliderSize(empty, &x, &y);

	if (Input::IsKeyDown(KEY::KEY_Z))--x;
	if (Input::IsKeyDown(KEY::KEY_X))++x;
	if (Input::IsKeyDown(KEY::KEY_C))--y;
	if (Input::IsKeyDown(KEY::KEY_V))++y;
	map->SetColliderSize(empty, &x, &y);

	printfDx("x : %d, y : %d\n", x, y);

//	DEBUG_LOG("hogehoge");
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
