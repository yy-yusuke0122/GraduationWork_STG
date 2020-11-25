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

	void Next();

private:
	void ChangeMode();
private:
	float count;
	int pattern;
	int nextPattern;

	Component* state;

};