#pragma once
#include "Collider3D.h"
#include "typedef.h"

class SphereCollider;

class BoxCollider : public Collider3D {
public:
	BoxCollider();
	~BoxCollider();

	void Disp();
	bool IsCollide(Collider3D* _collider) override;
	void SetPosition(VECTOR3 _pos) override;

	VECTOR3 GetDirect(int elem);	// 指定軸番号の方向ベクトルを取得
	float GetLen_W(int elem);		// 指定軸方向の長さを取得
	void Rotate(VECTOR3 _axis, float _deg);	// OBBを回転させる
	void SetLength(int elem, float len);	// 指定軸の長さを設定

private:
	OBB obb;

private:
	bool IsCollideCircle(SphereCollider* _collider);
	bool IsCollideBox(BoxCollider* _collider);
};
