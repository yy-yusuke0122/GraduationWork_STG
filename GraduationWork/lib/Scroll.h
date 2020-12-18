#pragma once

//#include "typedef.h"
#include "Quake.h"

class Object;

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
//	static void Initialize();

	static void Update();

	/// <summary>
	/// 現在のスクロール値取得
	/// </summary>
	/// <returns>スクロール値</returns>
	static const VECTOR2& GetValue() { return scrollValue; }

private:
	static void ScrollUpdate();

private:
	static VECTOR2 scrollValue;

public:
	static bool isUseDeltaTime;//スクロール値変化にDeltaTime()を使用するか

	static VECTOR2 value;//スクロール目的値

	static VECTOR2 speed;//スクロール速さ（0～1）

	static Quake quake;

};
