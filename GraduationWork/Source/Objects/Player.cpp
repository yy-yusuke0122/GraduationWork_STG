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
	imageRenderer = AddComponent<ImageRenderer>();	// �摜�`��@�\
	life = AddComponent<Life>();					// ���C�t�@�\
	animator2D = AddComponent<Animator2D>();		// �A�j���[�V�����@�\
	playerController = AddComponent<PlayerController>();		// �ړ��@�\�E�U���@�\
													// �~��̓����蔻��@�\
													// etc...

	// �R���|�[�l���g���̐ݒ�
	imageRenderer->SetImage("Media/Player.png");	// �`�悷��摜���Z�b�g
}

void Player::Update()
{
}
