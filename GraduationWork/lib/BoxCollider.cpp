#include "BoxCollider.h"
#include "UrLib.h"
#include "SphereCollider.h"

BoxCollider::BoxCollider()
{
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Disp()
{
	VECTOR3 c = GetWorldPosition();
	VECTOR3 left = obb.GetDirect(0) * obb.GetLen_W(0) * -1.0f;
	VECTOR3 right = obb.GetDirect(0) * obb.GetLen_W(0);
	VECTOR3 top = obb.GetDirect(1) * obb.GetLen_W(1) * -1.0f;
	VECTOR3 bottom = obb.GetDirect(1) * obb.GetLen_W(1);
	VECTOR3 front = obb.GetDirect(2) * obb.GetLen_W(2);
	VECTOR3 back = obb.GetDirect(2) * obb.GetLen_W(2) * -1.0f;
	VECTOR3 v[8] = {
		c + left + top + front,
		c + left + top + back,
		c + left + bottom + back,
		c + left + bottom + front,
		c + right + top + front,
		c + right + top + back,
		c + right + bottom + back,
		c + right + bottom + front
	};

	DrawLine((int)v[0].x, (int)v[0].y, (int)v[1].x, (int)v[1].y, GetColor(255, 255, 255));
	DrawLine((int)v[1].x, (int)v[1].y, (int)v[2].x, (int)v[2].y, GetColor(255, 255, 255));
	DrawLine((int)v[2].x, (int)v[2].y, (int)v[3].x, (int)v[3].y, GetColor(255, 255, 255));
	DrawLine((int)v[3].x, (int)v[3].y, (int)v[0].x, (int)v[0].y, GetColor(255, 255, 255));
	DrawLine((int)v[0].x, (int)v[0].y, (int)v[4].x, (int)v[4].y, GetColor(255, 255, 255));
	DrawLine((int)v[1].x, (int)v[1].y, (int)v[5].x, (int)v[5].y, GetColor(255, 255, 255));
	DrawLine((int)v[2].x, (int)v[2].y, (int)v[6].x, (int)v[6].y, GetColor(255, 255, 255));
	DrawLine((int)v[3].x, (int)v[3].y, (int)v[7].x, (int)v[7].y, GetColor(255, 255, 255));
	DrawLine((int)v[4].x, (int)v[4].y, (int)v[5].x, (int)v[5].y, GetColor(255, 255, 255));
	DrawLine((int)v[5].x, (int)v[5].y, (int)v[6].x, (int)v[6].y, GetColor(255, 255, 255));
	DrawLine((int)v[6].x, (int)v[6].y, (int)v[7].x, (int)v[7].y, GetColor(255, 255, 255));
	DrawLine((int)v[7].x, (int)v[7].y, (int)v[4].x, (int)v[4].y, GetColor(255, 255, 255));
}

bool BoxCollider::IsCollide(Collider3D* _collider)
{
	SphereCollider* col_c = dynamic_cast<SphereCollider*>(_collider);
	BoxCollider* col_b = dynamic_cast<BoxCollider*>(_collider);
	if (col_c != nullptr) {	// ‘ÎÛ‚ªCircleCollider‚ÌŽž
		return IsCollideCircle(col_c);
	}
	else if (col_b != nullptr) { // ‘ÎÛ‚ªBoxCollider‚ÌŽž
		return IsCollideBox(col_b);
	}
	return false;
}

void BoxCollider::SetPosition(VECTOR3 _pos)
{
    position = _pos;
    obb.SetPosition(GetWorldPosition());
}

VECTOR3 BoxCollider::GetDirect(int elem)
{
    return obb.GetDirect(elem);
}

float BoxCollider::GetLen_W(int elem)
{
    return obb.GetLen_W(elem);
}

void BoxCollider::Rotate(VECTOR3 _axis, float _deg)
{
    VECTOR3 vec = VNorm(_axis);

    // ŠeŽ²‚ð‰ñ“]
    obb.Rotate(_axis, _deg);
}

void BoxCollider::SetLength(int elem, float len)
{
    obb.SetLength(elem, len);
}

bool BoxCollider::IsCollideCircle(SphereCollider* _collider)
{
	return false;
}

bool BoxCollider::IsCollideBox(BoxCollider* _collider)
{
	return ColOBBs(obb, _collider->obb);
}
