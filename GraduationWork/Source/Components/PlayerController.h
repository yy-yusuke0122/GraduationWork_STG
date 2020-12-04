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
	PlayerMover* mover;
	PlayerAttacker* attacker;
	JumpComponent* jumpComponent;
	PhysicalBehavior* physics;

	VECTOR2 faceDir;	// ê≥ñ ÇÃå¸Ç´
};