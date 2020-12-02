#include "DrawManager.h"
#include "Renderer.h"
#include "Light.h"

std::list<Renderer*> DrawManager::rendererList;
std::list<Light*> DrawManager::lightList;

void DrawManager::Destroy()
{
	rendererList.clear();
	lightList.clear();
}

void DrawManager::Draw()
{
	for (std::list<Light*>::iterator it = lightList.begin(), end = lightList.end(); it != end; ++it)
	{
		(*it)->Set();
	}

	for (std::list<Renderer*>::iterator it = rendererList.begin(), end = rendererList.end(); it != end; ++it)
	{
		if ((*it)->IsActive() && (*it)->isRendererEnable)
			(*it)->Draw();
	}
}

void DrawManager::AddRenderer(Renderer* _p)
{
	rendererList.emplace_back(_p);
}

bool DrawManager::EraseRenderer(Renderer* _p)
{
	for (std::list<Renderer*>::iterator it = rendererList.begin(), end = rendererList.end(); it != end; ++it) 
	{ 
		if ((*it) == _p) {
			rendererList.erase(it);
			return true;
		}	
	}
	return false; 
}

void DrawManager::AddRight(Light* _p)
{
	lightList.emplace_back(_p);
}

bool DrawManager::EraseLight(Light* _p)
{
	for (std::list<Light*>::iterator it = lightList.begin(), end = lightList.end(); it != end; ++it)
	{
		if ((*it) == _p) {
			lightList.erase(it);
			return true;
		}
	}
	return false;
}
