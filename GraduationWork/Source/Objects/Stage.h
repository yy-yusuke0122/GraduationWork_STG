#pragma once

#include "../../lib/UrLib.h"

class Stage :public GameObject
{
public:
	static float GetY();

public:
	Stage()
	{
	}

	~Stage()
	{
	}

	void Start()override;

private:

};
