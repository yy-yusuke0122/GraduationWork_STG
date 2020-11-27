#pragma once
#include "../../lib/UrLib.h"

class PlayerMover : public Component {
public:
	PlayerMover();
	~PlayerMover();
	void Start();
	void Update();
	void Move(bool _isRight);
	void Jump();

private:
	float speed;		// 横移動速度を格納する箱
	float jumpPower;	// 落下速度を格納する箱
						// 着地しているかどうかを格納する箱

private:
	void Fall();		// 落下処理
};