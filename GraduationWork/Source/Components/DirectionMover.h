#pragma once

#include "../../lib/UrLib.h"

//�^�[�Q�b�g�Ɍ������܂�

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
