#pragma once

#include "typedef.h"

class Scroll
{
private:
	Scroll()
	{
	}

	~Scroll()
	{
	}

public:
	static void Update();

	static const VECTOR2& GetValue() { return scrollValue; }

private:
	static VECTOR2 scrollValue;

public:
	static VECTOR2 value;//スクロール目的値

	static VECTOR2 velocity;//スクロール速度

};
