#include "../../lib/UrLib.h"
#include "EnemyShot.h"
#include "EnemyAttack01.h"

namespace
{
	constexpr float MASS = 1.f;
	constexpr float GRAVITY = 9.8f * MASS;
}

void EnemyAttack01::Start()
{
}

void EnemyAttack01::Update()
{
	float delta = Time::DeltaTime();

	jumpSpeed += GRAVITY * delta;
	time += delta;

	if (!isAttacked && time > attackTime)
	{
		isAttacked = true;
		EnemyShot* shot = Instantiate<EnemyShot>();
		shot->transform->position = transform->position;
		//		shot->targetPos = ;
	}
}

void EnemyAttack01::Jump()
{
	jumpSpeed = -jumpPower;
}

void EnemyAttack01::OnCollisionEnter2D(Collider2D* _collider)
{
	if (_collider->gameObject->tag == "Stage")
	{
		jumpSpeed = 0.f;
	}
}
