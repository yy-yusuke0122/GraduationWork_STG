#include "PlayerMover.h"
#include "../Objects/Stage.h"

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
	speed = 5.0f;		// �ړ����x�̐ݒ�
	jumpPower = 0.0f;	// �����̗������x��0
	randing = false;	// �J���͒��n���Ă��Ȃ�
}

void PlayerMover::Update()
{
	if (randing == false) {
			Fall();// ��������
	}
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
	randing = false;
}

void PlayerMover::Fall()
{
	// ���W�ɉ��Z
	VECTOR3 vec;
	vec = VGet(0.0f, jumpPower, 0.0f);
	transform->AddPosition(vec);

	// �W�����v�p���[������
	jumpPower += GRAVITY;

	// �����Ă�����u���n���Ă��邩�ǂ����v��true�ɂ��āA���W�̓X�e�[�W�̍����ɖ߂��i���킹��j
	// ���n�������ǂ����̔���
	ImageRenderer* p = GetComponent<ImageRenderer>();
	int size = p->GetSizeY();	// �摜�̏c��
	float h = Stage::GetY();	// �X�e�[�W�̍���
	float playerFoot = transform->position.y + size / 2;

	if (playerFoot > h) {
		VECTOR3 pos = transform->position;
		pos.y = h - size / 2;
		randing = true;

		transform->SetPosition(pos);
	}
}