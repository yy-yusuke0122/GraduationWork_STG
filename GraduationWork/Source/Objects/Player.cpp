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
	// コンポーネントのアタッチ
	playerController = AddComponent<PlayerController>();		// 移動機能・攻撃機能

	// コンポーネント毎の設定
	imageRenderer->SetImage("Media/Player.png");	// 描画する画像をセット
	life->SetMaxHP(3.0f);							// 最大HPを設定
	life->SetHP(3.0f);								// 初期HPを設定
	circleCollider2D->circle.r = (imageRenderer->GetSizeX() + imageRenderer->GetSizeY()) / 2.f;
}
