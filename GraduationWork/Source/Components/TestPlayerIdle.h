#pragma once
#include "../../lib/UrLib.h"

class TestPlayerManager;

class TestPlayerIdle : public Component {
public:
	TestPlayerIdle();
	~TestPlayerIdle();
	void Start();
	void Update();

private:
	void CheckMoveInput();
	void CheckAttackInput();

private:
	TestPlayerManager* manager;
	StateController* state;
};