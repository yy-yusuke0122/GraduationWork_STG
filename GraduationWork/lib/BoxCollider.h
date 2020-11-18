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

	VECTOR3 GetDirect(int elem);	// �w�莲�ԍ��̕����x�N�g�����擾
	float GetLen_W(int elem);		// �w�莲�����̒������擾
	void Rotate(VECTOR3 _axis, float _deg);	// OBB����]������
	void SetLength(int elem, float len);	// �w�莲�̒�����ݒ�

private:
	OBB obb;

private:
	bool IsCollideCircle(SphereCollider* _collider);
	bool IsCollideBox(BoxCollider* _collider);
};
