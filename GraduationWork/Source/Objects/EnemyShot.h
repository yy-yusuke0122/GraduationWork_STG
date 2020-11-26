#pragma once

#include "../../lib/UrLib.h"

class DirectionMover;

class EnemyShot :public GameObject
{
public:
	EnemyShot()
	{
	}

	~EnemyShot()
	{
	}

	void Start()override;

	void SetTargetPos(const VECTOR3& _pos);

private:
	DirectionMover* direction;
	ImageRenderer* image;
};
