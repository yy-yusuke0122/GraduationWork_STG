#pragma once
#include "../../lib/UrLib.h"

class PlayerMover;
class PlayerAttacker;
class JumpComponent;

class TestPlayerManager : public Component {
public:
	TestPlayerManager();
	~TestPlayerManager();
	void Start();
	void Update();

	/// <summary>
	/// 左を向く
	/// </summary>
	void FaceLeft();

	/// <summary>
	/// 右を向く
	/// </summary>
	void FaceRight();

	/// <summary>
	/// 顔の向きを取得
	/// </summary>
	/// <returns>顔の向きベクトル</returns>
	VECTOR3 GetFaceDir() const;

private:
	// 状態管理変数
	std::string currentState;	// 現在の状態
	VECTOR3 faceDir;			// 顔の向き
	StateController* state;		// 状態操作
	Component* stateComp;		// 状態毎のコンポーネント

	// 物理挙動変数
	JumpComponent* jumpComp;	// ジャンプコンポーネント
	PhysicalBehavior* physics;	// 物理挙動コンポーネント

	// 描画用変数
	ImageRenderer* renderer;	// 画像描画コンポーネント

private:
	void CheckLanding();
};