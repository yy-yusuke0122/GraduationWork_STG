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
	// コンポーネントのアタッチ
	imageRenderer = AddComponent<ImageRenderer>();	// 画像描画機能
	life = AddComponent<Life>();					// ライフ機能
													// 移動機能・攻撃機能
													// 円状の当たり判定機能
													// etc...

	// コンポーネント毎の設定
	imageRenderer->SetImage("Media/Player.png");	// 描画する画像をセット
}

void Player::Update()
{
}
