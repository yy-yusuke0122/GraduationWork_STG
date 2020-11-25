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
	// �R���|�[�l���g���̐ݒ�
	imageRenderer->SetImage("Media/Enemy.png");	// �`�悷��摜���Z�b�g
	circleCollider2D->circle.r = (imageRenderer->GetSizeX() + imageRenderer->GetSizeY()) / 2.f;

	enemyController = AddComponent<EnemyController>();		// �ړ��@�\�E�U���@�\
}
