#pragma once
#include "Character.h"

class EnemyController;

class Enemy : public Character {
public:
	Enemy();
	~Enemy();
	void Start() override;
	void Update() override;

private:
	EnemyController* enemyController;
};