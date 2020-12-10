#pragma once
#include "../../lib/UrLib.h"

class PlayerMover;
class PlayerAttacker;
class JumpComponent;

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
	StateController* state;
	PlayerMover* mover;
	PlayerAttacker* attacker;
	JumpComponent* jumpComponent;
	PhysicalBehavior* physics;

	VECTOR2 faceDir;	// ê≥ñ ÇÃå¸Ç´
};