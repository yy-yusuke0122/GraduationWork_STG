#include "PointLight.h"
#include "Transform.h"

void PointLight::Start()
{
	handle = CreatePointLightHandle(transform->position, radius, 1.f, 0.f, attenuation);
}

void PointLight::SetDerived()
{
	if (attenuation == 0.f)attenuation = 0.1f;
	
	SetLightPositionHandle(handle, transform->position);
	SetLightRangeAttenHandle(handle, radius, 1.f, 0.f, attenuation);
}
