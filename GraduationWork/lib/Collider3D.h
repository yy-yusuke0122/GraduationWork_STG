#pragma once
#include "Collider.h"
#include "dxlib/DxLib.h"
#include "typedef.h"

class Collider3D : public Collider {
public:
	Collider3D();
	virtual ~Collider3D();

	virtual bool IsCollide(Collider3D* _collider) = 0;

	/// <summary>
	/// 衝突時に呼ばれる関数を全て実行する
	/// </summary>
	/// <param name="_collider">衝突したオブジェクトのコライダー</param>
	void ExecuteAllCollisionEnter(Collider3D* _collider);

	/// <summary>
	/// 衝突中に呼ばれる関数を全て実行する
	/// </summary>
	/// <param name="_collider">衝突中のオブジェクトのコライダー</param>
	void ExecuteAllCollisionStay(Collider3D* _collider);

	/// <summary>
	/// 衝突終了時に呼ばれる関数を全て実行する
	/// </summary>
	/// <param name="_collider">衝突終了したオブジェクトのコライダー</param>
	void ExecuteAllCollisionExit(Collider3D* _collider);

	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>所有者を原点としたコライダーの座標</returns>
	VECTOR3 GetLocalPosition();

	/// <summary>
	/// ワールド座標上のコライダーの座標を取得
	/// </summary>
	/// <returns>ワールド座標上のコライダーの座標</returns>
	VECTOR3 GetWorldPosition();

	/// <summary>
	/// コライダーの座標を設定
	/// </summary>
	/// <param name="_pos">所有者を原点とした移動先の座標</param>
	virtual void SetPosition(VECTOR3 _pos);

protected:
	VECTOR3 position;
};