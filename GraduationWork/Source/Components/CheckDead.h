#pragma once

#include "../../lib/UrLib.h"

class Life;

class CheckDead :public Component
{
public:
	CheckDead()
	{
	}

	~CheckDead()
	{
	}

	void Start();

	void Update();

private:
	Life* playerLife;
	Life* enemyLife;

};
