#pragma once
#include "Collider2D.h"

class BoxCollider2D;

class CircleCollider2D : public Collider2D {
public:
	CircleCollider2D();
	~CircleCollider2D();

	void Disp();
	bool IsCollide(Collider2D* _collider) override;
	Point2D GetWorldPosition() override;

	Circle2D circle;

private:
	bool IsCollideCircle(CircleCollider2D* _collider);
	bool IsCollideBox(BoxCollider2D* _collider);
};
