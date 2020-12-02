#include "LoadingScene.h"

float LoadingScene::asyncLoadMin = 3.f;

void LoadingScene::Start()
{
	GameObject* p = Instantiate<GameObject>();
	ImageRenderer* r = p->AddComponent<ImageRenderer>();
	r->SetImage("Media/Loading.png");
	p->transform->position.x = static_cast<float>(UrLib::Screen::x - r->GetSizeX());
	p->transform->position.y = static_cast<float>(UrLib::Screen::y - r->GetSizeY());
}

void LoadingScene::Update()
{
}
