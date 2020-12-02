#pragma once
#include "Character.h"

class EnemyController;

class Enemy : public Character {
public:
	Enemy();
	~Enemy();
	void Start() override;

	void Dead()override;

	void AsyncEnd()override;

private:
	EnemyController* enemyController;
};