#include "Life.h"
#include "CheckDead.h"

void CheckDead::Start()
{
	playerLife = FindGameObject("Player")->GetComponent<Life>();
	enemyLife = FindGameObject("Enemy")->GetComponent<Life>();
}

void CheckDead::Update()
{

	if (playerLife != nullptr && playerLife->hp <= 0.f)
	{
		playerLife->gameObject->Destroy();
		playerLife = nullptr;
	}
	if (enemyLife != nullptr && enemyLife->hp <= 0.f)
	{
		enemyLife->gameObject->Destroy();
		enemyLife = nullptr;
	}
}
