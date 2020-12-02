#pragma once
#include "../../lib/UrLib.h"

class JumpComponent : public Component {
public:
	JumpComponent();
	~JumpComponent();
	void Start() override;
	void Update() override;

	/// <summary>
	/// ジャンプする
	/// ジャンプ回数が上限を超える場合無視する
	/// </summary>
	void Jump();

	/// <summary>
	/// ジャンプ方向を設定する
	/// </summary>
	/// <param name="_dir">方向ベクトル</param>
	void SetJumpDir(VECTOR2 _dir);

	float jumpPower;			// ジャンプ力
	unsigned int jumpCount;		// ジャンプ回数
	unsigned int maxJumpCount;	// ジャンプ回数の最大数
	VECTOR2 localGravity;		// 重力ベクトル
private:
	VECTOR2 jumpDir;			// ジャンプ方向
	VECTOR2 fallVec;			// 落下ベクトル
	bool isLanding;				// 着地しているか
};
