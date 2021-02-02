#include "Enemy.h"
#include "../Components/Life.h"
#include "../Components/EnemyController.h"
#include "../Components/EnemyImageChanger.h"

namespace
{
	constexpr float MAX_HP = 50.f;
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Start()
{
	// コンポーネント毎の設定
	imageRenderer->SetImage("Media/Enemy.png");	// 描画する画像をセット

	AddComponent<EnemyImageChanger>();
	enemyController = AddComponent<EnemyController>();		// 移動機能・攻撃機能

	life->SetMaxHP(MAX_HP);
	life->SetHP(life->max);

	transform->SetPosition(VECTOR3(0.0f, 250.0f, 0.0f));
}

void Enemy::Dead()
{
	Destroy();
}

void Enemy::AsyncEnd()
{
	circleCollider2D->circle.r = (imageRenderer->GetSizeX() + imageRenderer->GetSizeY()) / 4.f;
}
