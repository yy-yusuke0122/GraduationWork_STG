#include "PlayerMover.h"

namespace {
	const float JUMP_POWER = 15.0f;//�㏸��
	const float GRAVITY = 0.5f;//�~����
}

PlayerMover::PlayerMover()
{
}

PlayerMover::~PlayerMover()
{
}

void PlayerMover::Start()
{
	speed = 5.0f;
	jumpPower = 0.0f;
}

void PlayerMover::Update()
{
	// ���W�ɉ��Z
	VECTOR3 vec;
	vec = VGet(0.0f, jumpPower, 0.0f);
	transform->AddPosition(vec);

	// �W�����v�p���[������
	jumpPower += GRAVITY;
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
	jumpPower = -JUMP_POWER;
}
