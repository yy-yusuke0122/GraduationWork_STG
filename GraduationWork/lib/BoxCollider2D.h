#pragma once
#include "Collider2D.h"

class CircleCollider2D;

class BoxCollider2D : public Collider2D {
public:
	BoxCollider2D();
	~BoxCollider2D();

	void Disp();
	bool IsCollide(Collider2D* _collider) override;
	Point2D GetWorldPosition() override;

	// ‰ñ“]Œã‚Ì’¸“_À•W‚Ìæ“¾
	Point2D LeftTop();
	Point2D LeftBottom();
	Point2D RightTop();
	Point2D RightBottom();

	AABB2D box;
	float rotation;

private:
	bool IsCollideCircle(CircleCollider2D* _collider);
	bool IsCollideBox(BoxCollider2D* _collider);
};
