#include "PlayerMover.h"

namespace {
	const float JUMP_POWER = 15.0f;//上昇量
	const float GRAVITY = 0.5f;//降下量
}

PlayerMover::PlayerMover()
{
}

PlayerMover::~PlayerMover()
{
}

void PlayerMover::Start()
{
	speed = 5.0f;		// 移動速度の設定
	jumpPower = 0.0f;	// 初期の落下速度は0
						// 開幕は着地していない
}

void PlayerMover::Update()
{
	// ↓（もし）着地していないなら呼ぶ
	// 落下処理
	Fall();
}

void PlayerMover::Move(bool _isRight)
{
	VECTOR3 vec;
	if (_isRight == true) {
		vec = VGet(speed, 0.0f, 0.0f);
	}
	else if (_isRight == false) {
		vec = VGet(-speed, 0.0f, 0.0f);
	}
	transform->AddPosition(vec);
}

void PlayerMover::Jump()
{
	jumpPower = -JUMP_POWER;
}

void PlayerMover::Fall()
{
	// 座標に加算
	VECTOR3 vec;
	vec = VGet(0.0f, jumpPower, 0.0f);
	transform->AddPosition(vec);

	// ジャンプパワーを減少
	jumpPower += GRAVITY;

	// ↓していたら「着地しているかどうか」をtrueにして、座標はステージの高さに戻す（合わせる）
	// 着地したかどうかの判定

}
