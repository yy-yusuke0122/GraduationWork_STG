#include "../../lib/UrLib.h"
#include "../Objects/EnemyShot.h"
#include "EnemyAttack00.h"
#include "EnemyController.h"
#include "../Objects/Stage.h"

namespace
{
	constexpr float MASS = 100.f;
	constexpr float GRAVITY = 9.8f * MASS;
	constexpr float JUMP_POWER = GRAVITY * 0.7f;
}

EnemyAttack00::EnemyAttack00() :
	jumpSpeed(0.f), attackTime(0.3f), time(0.f), isAttacked(false), isInitialize(false)
{
}

void EnemyAttack00::Start()
{
	Jump();
	isAttacked = false;
	time = 0.f;

	if ( ! isInitialize)
	{
		controller = GetComponent<EnemyController>();
		circle = GetComponent<CircleCollider2D>();
		isInitialize = true;
	}
}

void EnemyAttack00::Update()
{
	float delta = Time::DeltaTime();

	jumpSpeed += GRAVITY * delta;

	transform->position.y += jumpSpeed * delta;

	time += delta;
	
	if ( ! isAttacked && time > attackTime)
	{
		isAttacked = true;
		GameObject* player = FindGameObject("Player");
		if (player != nullptr)
		{
			EnemyShot* shot = Instantiate<EnemyShot>();
			shot->transform->SetPosition(transform->position);
			shot->SetTargetPos(player->transform->position);
		}
	}

#ifdef _DEBUG
	FindGameObject("Stage")->GetComponent<BoxCollider2D>()->Disp();
	circle->Disp();
#endif // _DEBUG

}

void EnemyAttack00::Jump()
{
	jumpSpeed = -JUMP_POWER;
}

void EnemyAttack00::OnCollisionEnter2D(Collider2D* _collider)
{
	if (_collider->gameObject->tag == "Stage")
	{
		transform->position.y = Stage::GetY() - circle->circle.r;
		controller->Next();
	}
}
