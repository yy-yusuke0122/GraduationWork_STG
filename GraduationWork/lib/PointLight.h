#pragma once

#include "Light.h"

class PointLight :public Light
{
public:
	PointLight() :
		radius(200.f), attenuation(0.001f) {}

	~PointLight()
	{
	}

private:
	void Start()override;

private:
	void SetDerived()override;

public:
	float radius;		//���a

	float attenuation;	//�����F������2�恖attenuation

};
