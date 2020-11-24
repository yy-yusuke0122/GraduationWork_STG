#include "../../lib/UrLib.h"
#include "EnemyShot.h"
#include "EnemyAttack00.h"

namespace
{
	constexpr float MASS = 1.f;
	constexpr float GRAVITY = 9.8f * MASS;
}

void EnemyAttack00::Start()
{
}

void EnemyAttack00::Update()
{
	float delta = Time::DeltaTime();

	jumpSpeed += GRAVITY * delta;
	time += delta;
	
	if (!isAttacked && time > attackTime)
	{
		isAttacked = true;
		EnemyShot* shot = Instantiate<EnemyShot>();
		shot->transform->position = transform->position;
		shot->SetTargetPos(gameObject->GetScene()->FindGameObject("Player")->transform->position);
	}
}

void EnemyAttack00::Jump()
{
	jumpSpeed = -jumpPower;
}

void EnemyAttack00::OnCollisionEnter2D(Collider2D* _collider)
{
	if (_collider->gameObject->tag == "Stage")
	{
		jumpSpeed = 0.f;
		
	}
}
