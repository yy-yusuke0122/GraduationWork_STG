#pragma once
#include "../../lib/UrLib.h"

class TestPlayerAttack : public Component {
public:
	TestPlayerAttack();
	~TestPlayerAttack();
	void Start();
	void Update();

private:
	void Attack();

private:
	StateController* state;

	int attackCount;
	float attackTime;
};