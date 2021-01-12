#include "Renderer.h"
#include "DrawManager.h"

Renderer::Renderer() :
	isRendererEnable(true), order(0)
{
	orderIt = DrawManager::AddRenderer(this);
}

Renderer::~Renderer()
{
	DrawManager::EraseRenderer(this);
}

void Renderer::SetOrder(int _order)
{
	order = _order;
	orderIt = DrawManager::AddRenderer(orderIt);
}
