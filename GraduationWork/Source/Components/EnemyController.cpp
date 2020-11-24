#include "EnemyController.h"
#include "EnemyAttack00.h"
#include "EnemyAttack01.h"

EnemyController::EnemyController()
{
}

EnemyController::~EnemyController()
{
}

void EnemyController::Start()
{
	state = AddComponent<EnemyAttack00>();
	AddComponent<EnemyAttack01>()->SetActive(false);
	pattern = 0;
}

void EnemyController::Update()
{
	count += Time::DeltaTime();
	if (count > 1.0f) {
		count = 0;
		ChangeMode();
	}
}

void EnemyController::ChangeMode()
{
	state->SetActive(false);
	switch (pattern) {
	case 0:
		state = GetComponent<EnemyAttack01>();
		pattern = 1;
		break;
	case 1:
		state = GetComponent<EnemyAttack00>();
		pattern = 0;
		break;
	default:
		break;
	}
	state->SetActive(true);
}
