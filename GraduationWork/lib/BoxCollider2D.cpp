#include "BoxCollider2D.h"
#include "UrLib.h"
#include "CircleCollider2D.h"

BoxCollider2D::BoxCollider2D() :
	rotation(0.0f)
{
	box.hl.x = 0.5f;
	box.hl.y = 0.5f;
}

BoxCollider2D::~BoxCollider2D()
{
}

void BoxCollider2D::Disp()
{
	AABB2D dispBox = box;
	dispBox.p = GetWorldPosition() - Scroll::GetValue();
	DrawRotaBox(dispBox, rotation, GetColor(255, 255, 255), FALSE);
	printfDx("rotation = %f\n", rotation);
}

bool BoxCollider2D::IsCollide(Collider2D* _collider)
{
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

Point2D BoxCollider2D::GetWorldPosition()
{
	Point p = transform->position + box.p;
	return Point2D(p.x, p.y);
}

AABB2D BoxCollider2D::GetAABB2D()
{
	AABB2D box;
	box.p = GetWorldPosition();

	Point2D p;
	auto SetMaxPoint = [&](Point2D _p) { 
		if (p.x < _p.x) p.x = _p.x;
		if (p.y < _p.y) p.y = _p.y;
	};

	SetMaxPoint(LeftTop());
	SetMaxPoint(RightTop());
	SetMaxPoint(RightBottom());
	SetMaxPoint(LeftBottom());

	box.hl = p;
	return box;
}

Point2D BoxCollider2D::LeftTop()
{
	Point2D p = box.LeftTop();
	Point2D p2 = { p.x * cosf(rotation) + p.y * -sinf(rotation), p.x * sinf(rotation) + p.y * cosf(rotation) };
	return p2 + GetWorldPosition() + box.p;
}

Point2D BoxCollider2D::LeftBottom()
{
	Point2D p = box.LeftBottom();
	Point2D p2 = { p.x * cosf(rotation) + p.y * -sinf(rotation), p.x * sinf(rotation) + p.y * cosf(rotation) };
	return p2 + GetWorldPosition() + box.p;
}

Point2D BoxCollider2D::RightTop()
{
	Point2D p = box.RightTop();
	Point2D p2 = { p.x * cosf(rotation) + p.y * -sinf(rotation), p.x * sinf(rotation) + p.y * cosf(rotation) };
	return p2 + GetWorldPosition() + box.p;
}

Point2D BoxCollider2D::RightBottom()
{
	Point2D p = box.RightBottom();
	Point2D p2 = { p.x * cosf(rotation) + p.y * -sinf(rotation), p.x * sinf(rotation) + p.y * cosf(rotation) };
	return p2 + GetWorldPosition() + box.p;
}

bool BoxCollider2D::IsCollideCircle(CircleCollider2D* _collider)
{
	// 矩形０度の時の座標に円の座標を直す
	Point2D rect = GetWorldPosition();
	Point2D c;

	{
		Point2D circle = _collider->GetWorldPosition();
		VECTOR2 tmp = circle - rect;
		tmp.Rotate(rotation);
		c = tmp + rect;
	}

	// 円の中心点から矩形の１番近い頂点の座標
	Point2D p;

	// 短径の頂点座標
	Point2D lt(box.LeftTop() + rect);
	Point2D rb(box.RightBottom() + rect);

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
	float radius = _collider->circle.r;
	float distance = (c - p).Length();
	if (distance < radius)
		return true; // 衝突

	// 円の中心点と長方形のあたり判定
	bool a = c.x > lt.x && c.x < rb.x && c.y > lt.y - radius && c.y < rb.y + radius;
	bool b = c.x > lt.x - radius && c.x < rb.x + radius && c.y > lt.y && c.y < rb.y;
	if (a || b)  return true;
	else return false;
}

bool BoxCollider2D::IsCollideBox(BoxCollider2D* _collider)
{
	// 自分の頂点
	Point2D myP[4];
	myP[0] = LeftTop();
	myP[1] = RightTop();
	myP[2] = RightBottom();
	myP[3] = LeftBottom();
	// 相手の頂点
	Point2D pairP[4];
	pairP[0] = _collider->LeftTop();
	pairP[1] = _collider->RightTop();
	pairP[2] = _collider->RightBottom();
	pairP[3] = _collider->LeftBottom();

	// 自分を構成する４辺のベクトル
	VECTOR2 myVec[4];
	myVec[0] = myP[1] - myP[0];
	myVec[1] = myP[2] - myP[1];
	myVec[2] = myP[3] - myP[2];
	myVec[3] = myP[0] - myP[3];
	// 自分を構成する４辺のベクトル
	VECTOR2 pairVec[4];
	pairVec[0] = pairP[1] - pairP[0];
	pairVec[1] = pairP[2] - pairP[1];
	pairVec[2] = pairP[3] - pairP[2];
	pairVec[3] = pairP[0] - pairP[3];

	// 当たり判定確認
	for (int i = 0; i < 4; ++i) { // ４頂点チェック
		bool isHit = true;
		VECTOR2 v[4];
		v[0] = pairP[i] - myP[0];
		v[1] = pairP[i] - myP[1];
		v[2] = pairP[i] - myP[2];
		v[3] = pairP[i] - myP[3];
		for (int j = 0; j < 4; ++j) {
			float dot = myVec[j].Cross(v[j]);
			if (dot < 0.0f) {
				isHit = false;
				break;
			}
		}
		if (isHit) return true;
	}
	for (int i = 0; i < 4; ++i) { // ４頂点チェック
		bool isHit = true;
		VECTOR2 v[4];
		v[0] = myP[i] - pairP[0];
		v[1] = myP[i] - pairP[1];
		v[2] = myP[i] - pairP[2];
		v[3] = myP[i] - pairP[3];
		for (int j = 0; j < 4; ++j) {
			float dot = pairVec[j].Cross(v[j]);
			if (dot < 0.0f) {
				isHit = false;
				break;
			}
		}
		if (isHit) return true;
	}

	return false;
}
