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
	nextPattern = pattern = 0;
}

void EnemyController::Update()
{
	if (pattern != nextPattern)
		ChangeMode();

	//count += Time::DeltaTime();
	//if (count > 1.0f) {
	//	count = 0;
	//	ChangeMode();
	//}
}

void EnemyController::Next()
{
	switch (pattern) {
	case 0:nextPattern = 1; break;
	case 1:nextPattern = 0; break;
	default:
		break;
	}
}

void EnemyController::ChangeMode()
{
	pattern = nextPattern;

	state->SetActive(false);
	switch (pattern) {
	case 0:
		state = GetComponent<EnemyAttack00>();
		break;
	case 1:
		state = GetComponent<EnemyAttack01>();
		break;
	default:
		break;
	}
	state->SetActive(true);
	state->Start();
}
