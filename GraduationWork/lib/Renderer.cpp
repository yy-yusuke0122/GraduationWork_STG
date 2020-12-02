#include "Renderer.h"
#include "DrawManager.h"

Renderer::Renderer() :
	isRendererEnable(true)
{
	DrawManager::AddRenderer(this);
}

Renderer::~Renderer()
{
	DrawManager::EraseRenderer(this);
}
