#pragma once

#include "Light.h"
#include "Function.h"

class SpotLight :public Light
{
public:
	SpotLight() :
		inRadian(ToRadian(45.f)), outRadian(ToRadian(15.f)), attenuation(0.1f), radius(1.f) {}

	~SpotLight()
	{
	}

private:
	void Start()override;

private:
	void SetDerived()override;

public:
	float inRadian;		//�����p�x
	float outRadian;	//�O���p�x

	float attenuation;	//������2�恖attenuation

	float radius;		//���a

};
