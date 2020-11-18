#include "DirectionalLight.h"
#include "Transform.h"

void DirectionalLight::Start()
{
	handle = CreateDirLightHandle(transform->GetForward());
}

void DirectionalLight::SetDerived()
{
	SetLightDirectionHandle(handle, transform->GetForward());
}
