#pragma once
#include "Collider3D.h"

class BoxCollider;

class SphereCollider : public Collider3D {
public:
	SphereCollider();
	~SphereCollider();

	void Disp();
	bool IsCollide(Collider3D* _collider) override;
	void SetRadius(float _radius) { radius = _radius; }
	float GetRadius()const { return radius; }

private:
	float radius;

private:
	bool IsCollideCircle(SphereCollider* _collider);
	bool IsCollideBox(BoxCollider* _collider);
};
