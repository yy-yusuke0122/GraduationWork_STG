#include "Player.h"
#include "../Components/Life.h"
#include "../Components/TestPlayerManager.h"

Player::Player() :
	playerController(nullptr)
{
}

Player::~Player()
{
}

void Player::Start()
{
	// �R���|�[�l���g�̃A�^�b�`
	playerController = AddComponent<TestPlayerManager>();		// �ړ��@�\�E�U���@�\

	// �R���|�[�l���g���̐ݒ�
	life->SetMaxHP(50.0f);							// �ő�HP��ݒ�
	life->SetHP(life->max);							// ����HP��ݒ�
	circleCollider2D->circle.r = 4.0f;
}
