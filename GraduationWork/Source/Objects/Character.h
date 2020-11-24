#pragma once
#include "../../lib/UrLib.h"

class Life;

class Character : public GameObject {
public:
	Character();
	virtual ~Character();
	virtual void Start();
	virtual void Update();
protected:
	ImageRenderer* imageRenderer;
	Life* life;
};