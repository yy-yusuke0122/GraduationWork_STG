#include "Renderer.h"
#include "DrawManager.h"

Renderer::Renderer() :
	isRendererEnable(true)
{
	DrawManager::Get()->AddRenderer(this);
}

Renderer::~Renderer()
{
	DrawManager::Get()->EraseRenderer(this);
}
