#include "TestBullet.h"
#include "../Components/ProjectileMoveMent.h"

TestBullet::TestBullet()
{
}

TestBullet::~TestBullet()
{
}

void TestBullet::Start()
{
	GameObject* player = FindGameObject("Player");
	transform->SetPosition(player->transform->position);

	AddComponent<ImageRenderer>()->SetImage("Media/TestBullet.png");
	AddComponent<CircleCollider2D>();
	ProjectileMoveMent* comp = AddComponent<ProjectileMoveMent>();
	comp->direction = transform->GetRight();
	comp->speed = 10.0f;

	PhysicalBehavior* physics = AddComponent<PhysicalBehavior>();
	physics->gravity = 10.f;
}
