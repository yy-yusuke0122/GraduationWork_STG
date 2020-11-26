#include "EnemyController.h"
#include "../Objects/EnemyShot.h"
#include "EnemyImageChanger.h"
#include "EnemyAttack02.h"

namespace
{
	//重力定数
	constexpr float MASS = 20.f;
	constexpr float GRAVITY = 9.8f * MASS;
	constexpr float JUMP_POWER = GRAVITY * 1.5f;

	//ショット定数
	constexpr int SHOT_MAX = 8;

	//時間定数
	constexpr float START_BLANK = 0.5f;
	constexpr float SHOT_BLANK = 0.2f;

	//移動定数
//	constexpr float XSPEED = 150.f;
}

EnemyAttack02::EnemyAttack02() :
	jumpSpeed(0.f), time(0.f), isInitialize(false), shotCount(0)
{
}

void EnemyAttack02::Start()
{
	time = -START_BLANK;

	jumpSpeed = -JUMP_POWER;

	shotCount = SHOT_MAX;

	if ( ! isInitialize)
	{
		isInitialize = true;
		controller = GetComponent<EnemyController>();
		changer = GetComponent<EnemyImageChanger>();
		renderer = GetComponent<ImageRenderer>();
	}
	else
	{
		changer->SetActive(false);

		renderer->turnXFlag = (UrLib::Screen::x / 2.f) > transform->position.x;
	}

	xspeed = (UrLib::Screen::x - 2.f * transform->position.x) / (2.f * JUMP_POWER / GRAVITY);
	//y = v0t - 1/2gt^2(v0 = JUMP_POWER, y = 0)
	//0 = JUMP_POWER*t - 1/2*g*t^2
	//t = 2*JUMP_POWER / g
}

void EnemyAttack02::Update()
{
	float delta = Time::DeltaTime();

	time += delta;

	jumpSpeed += GRAVITY * delta;

	transform->position.y += jumpSpeed * delta;

	transform->position.x += xspeed * delta;

	if (SHOT_BLANK < time)
	{
		time = 0.f;
		if (shotCount > 0)
		{
			--shotCount;
			EnemyShot* p = Instantiate<EnemyShot>();
			p->transform->position = transform->position;
			p->SetTargetPos(GetScene()->FindGameObject("Player")->transform->position);
		}
	}
}

void EnemyAttack02::OnCollisionEnter2D(Collider2D* _collider)
{
	if (_collider->gameObject->tag == "Stage")
	{
		controller->Next();
		changer->SetActive(true);
	}
}
