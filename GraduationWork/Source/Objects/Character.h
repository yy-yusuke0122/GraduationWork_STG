#pragma once
#include "../../lib/UrLib.h"

class Life;

class Character : public GameObject {
public:
	Character();
	virtual ~Character();
	virtual void Start();

protected:
	ImageRenderer* imageRenderer;
	Life* life;
	CircleCollider2D* circleCollider2D;
};