#pragma once
#include "../../lib/UrLib.h"

class Jump : public Component {
public:
	Jump();
	~Jump();
	void Start();
	void Update();

private:
	float power;
	float speed;
	float gravity;
};