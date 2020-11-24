#pragma once
#include "../../lib/UrLib.h"

class PlayerMover;

class PlayerController : public Component {
public:
	PlayerController();
	~PlayerController();
	void Start();
	void Update();

private:
	PlayerMover* playerMover;
};