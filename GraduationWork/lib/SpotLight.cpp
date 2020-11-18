#include "SpotLight.h"
#include "Transform.h"

void SpotLight::Start()
{
	handle = CreateSpotLightHandle(
		transform->position, transform->GetForward(), outRadian, inRadian, radius, 1.f, 0.f, attenuation);
}

void SpotLight::SetDerived()
{
	if (attenuation == 0.f)attenuation = 0.1f;

	float out = inRadian + outRadian;

	Clamp(out, 0.f, DX_PI_F);
	Clamp(inRadian, 0.f, out);
	outRadian = out - inRadian;

	SetLightDirectionHandle(handle, transform->GetForward());
	SetLightPositionHandle(handle, transform->position);
	SetLightRangeAttenHandle(handle, radius, 1.f, 0.f, attenuation);
	SetLightAngleHandle(handle, out, inRadian);
}
