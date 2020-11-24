#pragma once
#include "../../lib/UrLib.h"

class EnemyAttack00;
class EnemyAttack01;

class EnemyController : public Component {
public:
	EnemyController();
	~EnemyController();
	void Start();
	void Update();

private:
	void ChangeMode();
private:
	float count;
	int pattern;

	Component* state;
};