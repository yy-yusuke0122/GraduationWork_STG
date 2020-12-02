#pragma once

#include "AsyncComponent.h"

class Renderer :public AsyncComponent
{
public:
	Renderer();
	virtual ~Renderer();

	/// <summary>
	/// •`‰æ
	/// </summary>
	virtual void Draw() = 0;

private:
	void AsyncEnd()override { isRendererEnable = true; }

public:
	bool isRendererEnable;
	
};
