#include "PlayerMover.h"

PlayerMover::PlayerMover()
{
}

PlayerMover::~PlayerMover()
{
}

void PlayerMover::Start()
{
	speed = 1.0f;
}

void PlayerMover::Update()
{
}

void PlayerMover::Move(bool _isRight)
{
	VECTOR3 vec;
	if (_isRight == true) {
		vec = VGet(speed, 0.0f, 0.0f);
	}
	else if (_isRight == false) {
		vec = VGet(-speed, 0.0f, 0.0f);
	}
	transform->AddPosition(vec);
}

void PlayerMover::Jump()
{
}
