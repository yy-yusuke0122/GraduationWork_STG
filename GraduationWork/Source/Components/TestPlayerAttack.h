#pragma once
#include "../../lib/UrLib.h"

class TestPlayerManager;

class TestPlayerAttack : public Component {
public:
	TestPlayerAttack();
	~TestPlayerAttack();
	void Start();
	void Update();

private:
	void Attack();
	bool CanAttack();
	void CheckAxisInput();

private:
	TestPlayerManager* manager;
	StateController* state;

	int attackCount;
	float attackTime;
};