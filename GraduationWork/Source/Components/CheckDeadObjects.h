#pragma once

#include "../../lib/UrLib.h"

class Life;

class CheckDeadObjects :public Component
{
public:
	CheckDeadObjects()
	{
	}

	~CheckDeadObjects()
	{
		lifeList.clear();
	}

	void Start();

	void Update();

private:
	std::list<Life*> lifeList;

};
