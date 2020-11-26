#pragma once

#include "../../lib/UrLib.h"

class EnemyController;

class EnemyAttack01 :public Component
{
public:
	EnemyAttack01();

	~EnemyAttack01()
	{
	}

	void Start()override;

	void Update()override;

private:
	bool isInitialize;

	float time;

	EnemyController* controller;

};
