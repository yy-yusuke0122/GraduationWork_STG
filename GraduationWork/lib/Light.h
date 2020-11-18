#pragma once

#include "dxlib/DxLib.h"
#include "Component.h"

//TODO : 3つまでしかセットできないため、カメラ近くのライトのみを影響させる

class Light :public Component
{
public:
	struct COLOR
	{
		COLOR() :r(1.f), g(1.f), b(1.f) {}
		COLOR(float _r, float _g, float _b) :r(_r), g(_g), b(_b) {}
		float r, g, b;
	};
	static COLOR GetCOLOR(float _r, float _g, float _b) { return COLOR(_r, _g, _b); }
	static const COLOR red, green, blue, white, black;

public:
	Light();

	virtual ~Light();

	void Set();

	static int GetEnableCount();

private:
	virtual void SetDerived() = 0;

public:
	COLOR diffuse, specular, ambient;//0～1

protected:
	int handle;//ハンドル

};
