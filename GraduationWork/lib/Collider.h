#pragma once
#include "Component.h"

class Collider : public Component {
public:
	Collider();
	virtual ~Collider();

	void Disp() {}

private:
	bool isTrriger;
};