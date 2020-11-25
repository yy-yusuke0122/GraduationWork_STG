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
	// コンポーネントのアタッチ
	imageRenderer = AddComponent<ImageRenderer>();	// 画像描画機能
	life = AddComponent<Life>();					// ライフ機能
	CircleCollider2D* circle = AddComponent<CircleCollider2D>();// 円状の当たり判定機能
													// etc...

	// コンポーネント毎の設定
	imageRenderer->SetImage("Media/Enemy.png");	// 描画する画像をセット
	circle->circle.r = (imageRenderer->GetSizeX() + imageRenderer->GetSizeY()) / 2.f;

	enemyController = AddComponent<EnemyController>();		// 移動機能・攻撃機能
}
