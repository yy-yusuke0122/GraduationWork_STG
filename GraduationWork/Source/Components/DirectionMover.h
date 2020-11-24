#pragma once

#include "../../lib/UrLib.h"

//ターゲットに向かいます

class DirectionMover :public Component
{
public:
	DirectionMover() :
		speed(0.f), rad(0.f)
	{
	}

	~DirectionMover()
	{
	}

	void Start();

	void Update();

	float rad;

	float speed;

};
