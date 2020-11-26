#include "Player.h"
#include "../Components/Life.h"
#include "../Components/PlayerController.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	// �R���|�[�l���g�̃A�^�b�`
	playerController = AddComponent<PlayerController>();		// �ړ��@�\�E�U���@�\

	// �R���|�[�l���g���̐ݒ�
	imageRenderer->SetImage("Media/Player.png");	// �`�悷��摜���Z�b�g
	life->SetMaxHP(3.0f);							// �ő�HP��ݒ�
	life->SetHP(3.0f);								// ����HP��ݒ�
	circleCollider2D->circle.r = (imageRenderer->GetSizeX() + imageRenderer->GetSizeY()) / 2.f;
}
