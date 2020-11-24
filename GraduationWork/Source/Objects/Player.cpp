#include "Player.h"
#include "../Components/Life.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	// �R���|�[�l���g�̃A�^�b�`
	imageRenderer = AddComponent<ImageRenderer>();	// �摜�`��@�\
	life = AddComponent<Life>();					// ���C�t�@�\
													// �ړ��@�\�E�U���@�\
													// �~��̓����蔻��@�\
													// etc...

	// �R���|�[�l���g���̐ݒ�
	imageRenderer->SetImage("Media/Player.png");	// �`�悷��摜���Z�b�g
}

void Player::Update()
{
}
