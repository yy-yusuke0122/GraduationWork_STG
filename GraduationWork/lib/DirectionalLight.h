#pragma once

#include "Light.h"

class DirectionalLight :public Light
{
public:
	DirectionalLight() {}

	~DirectionalLight()
	{
	}

private:
	void Start()override;

private:
	void SetDerived()override;

public:

};
