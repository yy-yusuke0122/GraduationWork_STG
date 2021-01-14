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

public:
	/// <summary>
	/// •`‰æ‡‚ğİ’è
	/// </summary>
	/// <param name="_order">•`‰æ‡</param>
	void SetOrder(int _order);

	/// <summary>
	/// •`‰æ‡‚ğæ“¾
	/// </summary>
	/// <returns>•`‰æ‡</returns>
	int GetOrder()const { return order; }

private:
	void AsyncEnd()override { isRendererEnable = true; }

public:
	bool isRendererEnable;//•`‰æ ƒIƒ“EƒIƒt

private:
	std::list<Renderer*>::iterator orderIt;

	int order;//•`‰æ‚Ì‡”Ôi0‚ªæj

};
