#include "Light.h"
#include "DrawManager.h"
#include "Function.h"

namespace
{
	COLOR_F ClampColor(Light::COLOR& _color)
	{
		Clamp(_color.r, 0.f, 1.f);
		Clamp(_color.g, 0.f, 1.f);
		Clamp(_color.b, 0.f, 1.f);
		return GetColorF(_color.r, _color.g, _color.b, 1.f);
	}
}

const Light::COLOR Light::red = Light::GetCOLOR(1.f, 0.f, 0.f);
const Light::COLOR Light::green = Light::GetCOLOR(0.f, 1.f, 0.f);
const Light::COLOR Light::blue = Light::GetCOLOR(0.f, 0.f, 1.f);
const Light::COLOR Light::white = Light::GetCOLOR(1.f, 1.f, 1.f);
const Light::COLOR Light::black = Light::GetCOLOR(0.f, 0.f, 0.f);

Light::Light() :
	handle(-1), ambient(0.f, 0.f, 0.f)
{
	DrawManager::Get()->AddRight(this);
}

Light::~Light()
{
	DrawManager::Get()->EraseLight(this);
	if (handle != -1)
		DeleteLightHandle(handle);

}

void Light::Set()
{
	if (handle == -1)return;

	if (IsActive())
	{
		SetLightEnableHandle(handle, TRUE);
		SetLightDifColorHandle(handle, ClampColor(diffuse));
		SetLightSpcColorHandle(handle, ClampColor(specular));
		SetLightAmbColorHandle(handle, ClampColor(ambient));
		SetDerived();
	}
	else
		SetLightEnableHandle(handle, FALSE);

}

int Light::GetEnableCount()
{
	return GetEnableLightHandleNum();
}
