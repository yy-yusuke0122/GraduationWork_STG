#pragma once
#include "../../lib/UrLib.h"

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
	StateController* state;

	VECTOR3 dir;
	float speed;
};