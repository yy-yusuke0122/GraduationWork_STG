#include "Enemy.h"
#include "../Components/Life.h"
#include "../Components/EnemyController.h"
#include "../Components/EnemyImageChanger.h"

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
	circleCollider2D->circle.r = (imageRenderer->GetSizeX() + imageRenderer->GetSizeY()) / 4.f;

	AddComponent<EnemyImageChanger>();
	enemyController = AddComponent<EnemyController>();		// 移動機能・攻撃機能
}
