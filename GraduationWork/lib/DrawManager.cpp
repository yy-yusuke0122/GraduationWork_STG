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

std::list<Renderer*>::iterator DrawManager::AddRenderer(Renderer* _p)
{
	std::list<Renderer*>::iterator ret;

	for (std::list<Renderer*>::reverse_iterator it = rendererList.rbegin(),
		end = rendererList.rend(); it != end; ++it)
	{
		if ((*it)->GetOrder() > _p->GetOrder())
			continue;//オーダーが同じまたは小さいが見つかるまで
		return rendererList.emplace(it.base(), _p);
		break;
	}

	//自分が一番小さい
	rendererList.emplace_front(_p);
	return rendererList.begin();
}

std::list<Renderer*>::iterator DrawManager::AddRenderer(std::list<Renderer*>::iterator _p)
{
	Renderer* p = *_p;
	rendererList.erase(_p);
	return AddRenderer(p);
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

void DrawManager::AddLight(Light* _p)
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
