#pragma once
#include "../../lib/UrLib.h"

class PhysicalBehavior;

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
	/// 落下を終了させる
	/// 着地した時に呼ぶ関数
	/// </summary>
	void Land();

	/// <summary>
	/// ジャンプ方向を設定する
	/// </summary>
	/// <param name="_dir">方向ベクトル</param>
	void SetJumpDir(VECTOR3 _dir);

	float jumpPower;			// ジャンプ力
	unsigned int jumpCount;		// ジャンプ回数
	unsigned int maxJumpCount;	// ジャンプ回数の最大数

private:
	VECTOR3 jumpDir;			// ジャンプ方向
	PhysicalBehavior* physics;	// 物理挙動コンポーネント
};
