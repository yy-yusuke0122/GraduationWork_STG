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
	// コンポーネントのアタッチ
	playerController = AddComponent<TestPlayerManager>();		// 移動機能・攻撃機能

	// コンポーネント毎の設定
	imageRenderer->SetImage("Media/Player.png");	// 描画する画像をセット
	life->SetMaxHP(50.0f);							// 最大HPを設定
	life->SetHP(life->max);							// 初期HPを設定
	circleCollider2D->circle.r = 4.0f;
}
