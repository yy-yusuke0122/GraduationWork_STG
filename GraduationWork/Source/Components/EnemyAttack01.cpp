#include "../../lib/UrLib.h"
#include "../Objects/EnemyShot.h"
#include "EnemyAttack01.h"
#include "EnemyController.h"

namespace
{
	constexpr float TIME = 1.f;
}

EnemyAttack01::EnemyAttack01() :
	isInitialize(false)
{
}

void EnemyAttack01::Start()
{
	time = 0.f;

	if (!isInitialize)
	{
		controller = GetComponent<EnemyController>();
		isInitialize = true;
	}
}

void EnemyAttack01::Update()
{
	float delta = Time::DeltaTime();

	time += delta;

	if (time > TIME)
	{
		controller->Next();
	}

}
