#pragma once
#include "../../lib/UrLib.h"

class PlayerMover;
class PlayerAttacker;
class JumpComponent;

class PlayerController : public Component {
public:
	PlayerController();
	~PlayerController();
	void Start();
	void Update();

private:
	StateController* state;
	std::string currentState;
	Component* stateComp;

private:
	void CheckLanding();
};