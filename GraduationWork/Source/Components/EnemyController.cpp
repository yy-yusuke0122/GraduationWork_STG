#include "EnemyController.h"
#include "EnemyAttack00.h"
#include "EnemyAttack01.h"
#include "EnemyAttack02.h"

EnemyController::EnemyController()
{
}

EnemyController::~EnemyController()
{
}

void EnemyController::Start()
{
	(stateArray[0] = state = AddComponent<EnemyAttack00>())->SetActive(false);
	(stateArray[1] = AddComponent<EnemyAttack01>())->SetActive(false);
	(stateArray[2] = AddComponent<EnemyAttack02>())->SetActive(false);
	nextPattern = pattern = 0;
}

void EnemyController::Update()
{
	GetComponent<CircleCollider2D>()->Disp();
	return;
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
	switch (pattern)
	{
	case 0:nextPattern = 1; break;
	case 1:nextPattern = 2; break;
	case 2:nextPattern = 0; break;
	default:
		break;
	}
}

void EnemyController::ChangeMode()
{
	pattern = nextPattern;

	state->SetActive(false);
	
	state = stateArray[pattern];

	state->SetActive(true);
	state->Start();
}
