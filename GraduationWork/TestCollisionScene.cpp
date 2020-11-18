#include "TestCollisionScene.h"
#include "Player.h"
#include "TestTransformComponent.h"
#include "TestCollisionComponent.h"

TestCollisionScene::TestCollisionScene()
{
	player1 = Instantiate<Player>();
	player2 = Instantiate<Player>();
}

TestCollisionScene::~TestCollisionScene()
{
}

void TestCollisionScene::Start()
{
	player1->GetComponent<ImageRenderer>()->SetImage("..\\Media\\testCircle.png");
	player1->AddComponent<TestTransformComponent>()->UseControl(true);
	player1->AddComponent<TestCollisionComponent>();
	player2->GetComponent<ImageRenderer>()->SetImage("..\\Media\\testCircle.png");
	
	BoxCollider2D* boxCollider2D = player1->AddComponent<BoxCollider2D>();
	boxCollider2D->box.hl.x = 50.0f;
	boxCollider2D->box.hl.y = 50.0f;
	boxCollider2D = player2->AddComponent<BoxCollider2D>();
	boxCollider2D->box.hl.x = 100.0f;
	boxCollider2D->box.hl.y = 100.0f;

	player1->transform->SetPosition(VGet(300.0f, 200.0f, 0.0f));
	player2->transform->SetPosition(VGet(Screen::x * 0.5f, Screen::y * 0.5f, 0.0f));
}

void TestCollisionScene::Update()
{
	player1->GetComponent<BoxCollider2D>()->Disp();
	player2->GetComponent<BoxCollider2D>()->Disp();
}
