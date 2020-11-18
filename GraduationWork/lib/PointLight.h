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
	float radius;		//”¼Œa

	float attenuation;	//Œ¸ŠF‹——£‚Ì2æ–attenuation

};
