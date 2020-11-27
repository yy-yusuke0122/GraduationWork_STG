#include "Enemy.h"
#include "../Components/Life.h"
#include "../Components/EnemyController.h"
#include "../Components/EnemyImageChanger.h"

namespace
{

}

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
	circleCollider2D->circle.r = (imageRenderer->GetSizeX() + imageRenderer->GetSizeY()) / 4.f;

	AddComponent<EnemyImageChanger>();
	enemyController = AddComponent<EnemyController>();		// �ړ��@�\�E�U���@�\

	life->SetMaxHP(20.f);
	life->SetHP(life->max);
}
