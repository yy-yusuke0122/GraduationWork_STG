#pragma once
#include "../../lib/UrLib.h"

class TestPlayerManager;

class TestPlayerMove : public Component {
public:
	TestPlayerMove();
	~TestPlayerMove();
	void Start();
	void Update();

private:
	void CheckMoveInput();
	void Move();

private:
	TestPlayerManager* manager;
	ComponentSwitcher* state;

	VECTOR2 dir;
	float speed;
};