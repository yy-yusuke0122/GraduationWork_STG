#include "CircleCollider2D.h"
#include "UrLib.h"
#include "BoxCollider2D.h"

CircleCollider2D::CircleCollider2D()
{
}

CircleCollider2D::~CircleCollider2D()
{
}

void CircleCollider2D::Disp()
{
	VECTOR2 pos = GetWorldPosition() - Scroll::GetValue();
	DrawCircle((int)pos.x, (int)pos.y, (int)circle.r, GetColor(255, 255, 255), FALSE);
}

bool CircleCollider2D::IsCollide(Collider2D* _collider)
{
	// どちらかの有効状態が無効の場合は衝突していない
	if (!IsActive() || !_collider->IsActive())
		return false;

	CircleCollider2D* col_c = dynamic_cast<CircleCollider2D*>(_collider);
	BoxCollider2D* col_b = dynamic_cast<BoxCollider2D*>(_collider);
	if (col_c != nullptr) {	// 対象がCircleColliderの時
		return IsCollideCircle(col_c);
	}
	else if (col_b != nullptr) { // 対象がBoxColliderの時
		return IsCollideBox(col_b);
	}
	return false;
}

Point2D CircleCollider2D::GetWorldPosition()
{
	Point p = transform->position + circle.p;
	return Point2D(p.x, p.y);;
}

AABB2D CircleCollider2D::GetAABB2D()
{
	AABB2D box;
	box.p = GetWorldPosition();
	box.hl.x = this->circle.r;
	box.hl.y = this->circle.r;
	return box;
}

bool CircleCollider2D::IsCollideCircle(CircleCollider2D* _collider)
{
	Transform* tr1 = _collider->transform;
	Transform* tr2 = transform;
	VECTOR3 diff = tr1->position - tr2->position;
	float dist = VSize(diff);
	if (dist <= _collider->circle.r + circle.r) {
		return true;
	}

	return false;
}

bool CircleCollider2D::IsCollideBox(BoxCollider2D* _collider)
{
	// 矩形０度の時の座標に円の座標を直す
	Point2D origin_c = GetWorldPosition();
	float radian = ToRadian(_collider->rotation);
	Point2D rect = _collider->GetWorldPosition();
	Point2D c;

	c.x = cos(radian) * (origin_c.x - rect.x) - sin(radian) * (origin_c.y - rect.y) + rect.x;
	c.y = sin(radian) * (origin_c.x - rect.x) + cos(radian) * (origin_c.y - rect.y) + rect.y;

	// 円の中心点から矩形の１番近い頂点の座標
	Point2D p;

	// 短径の頂点座標
	Point2D lt(_collider->LeftTop());
	Point2D rb(_collider->RightBottom());

	// １番近いx座標を求める
	if (c.x < rect.x)
		p.x = lt.x;
	else if (c.x > rect.x)
		p.x = rb.x;
	else
		p.x = c.x;

	// １番近いy座標を求める
	if (c.y < rect.y)
		p.y = lt.y;
	else if (c.y > rect.y)
		p.y = rb.y;
	else
		p.y = c.y;

	// 一番近い角丸との衝突判定
	float distance = (c - p).Length();
	if (distance < circle.r)
		return true; // 衝突

	// 円の中心点と長方形のあたり判定
	bool a = c.x > lt.x && c.x < rb.x && c.y > lt.y - circle.r && c.y < rb.y + circle.r;
	bool b = c.x > lt.x - circle.r && c.x < rb.x + circle.r && c.y > lt.y && c.y < rb.y;
	if (a || b)  return true;
	else return false;
}
