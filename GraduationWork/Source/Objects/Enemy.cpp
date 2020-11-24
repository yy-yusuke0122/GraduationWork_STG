#include "Enemy.h"
#include "../Components/Life.h"
#include "../Components/EnemyController.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Start()
{
	// �R���|�[�l���g�̃A�^�b�`
	imageRenderer = AddComponent<ImageRenderer>();	// �摜�`��@�\
	life = AddComponent<Life>();					// ���C�t�@�\
	enemyController = AddComponent<EnemyController>();		// �ړ��@�\�E�U���@�\
													// �~��̓����蔻��@�\
													// etc...

	// �R���|�[�l���g���̐ݒ�
	imageRenderer->SetImage("Media/Enemy.png");	// �`�悷��摜���Z�b�g
}

void Enemy::Update()
{
}
