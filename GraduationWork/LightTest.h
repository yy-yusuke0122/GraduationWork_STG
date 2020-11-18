#pragma once

#include "lib/UrLib.h"

class LightTest :public GameObject
{
public:
	LightTest()
	{
	}

	~LightTest()
	{
		DeleteShadowMap(shadow);
	}

	void Start()override;

	void Update()override;

private:
	int shadow;
};
