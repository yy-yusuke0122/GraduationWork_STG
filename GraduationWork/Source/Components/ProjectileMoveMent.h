#pragma once
#include "../../lib/UrLib.h"

class ProjectileMoveMent : public Component {
public:
	ProjectileMoveMent();
	~ProjectileMoveMent();
	void Start();
	void Update();

	VECTOR3 direction;
	float speed;
};