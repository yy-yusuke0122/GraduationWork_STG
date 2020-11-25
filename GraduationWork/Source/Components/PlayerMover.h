#pragma once
#include "../../lib/UrLib.h"

class PlayerMover : public Component {
public:
	PlayerMover();
	~PlayerMover();
	void Start();
	void Update();
	void Move(bool _isRight);
	void Jump();

private:
	float speed;
	float jumpPower;
};