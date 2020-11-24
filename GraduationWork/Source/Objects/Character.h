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
	Animator2D* animator2D;
};