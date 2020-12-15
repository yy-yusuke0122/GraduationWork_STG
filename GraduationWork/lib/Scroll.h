#pragma once

#include "typedef.h"

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
	static void Update();

	/// <summary>
	/// 現在のスクロール値取得
	/// </summary>
	/// <returns>スクロール値</returns>
	static const VECTOR2& GetValue() { return scrollValue; }

	/// <summary>
	/// 震わせる
	/// </summary>
	static void Quake(const VECTOR2& _center) { isQuake = true; }

	/// <summary>
	/// 震えの終了時に呼び出す関数をセット
	/// 呼出し後に破棄
	/// </summary>
	/// <typeparam name="C">クラス型</typeparam>
	/// <param name="_obj">オブジェクトアドレス</param>
	/// <param name="_call">呼び出す関数</param>
	template<class C>
	static void QuakeEndCallback(C* _obj, void (C::* _call)())
	{
		callObj = _obj;
		cCallback = reinterpret_cast<void (Object::*)()> (_call);
	}

private:
	static void ScrollUpdate();

	static void QuakeUpdate();

	static void EndQuake();

private:
	static VECTOR2 scrollValue;

	static float time;

	static bool isQuake;

	static Object* callObj;
	static void (Object::*cCallback)();

public:
	static bool isUseDeltaTime;//スクロール値変化にDeltaTime()を使用するか

	static VECTOR2 value;//スクロール目的値、Quake時→原点とする

	static VECTOR2 speed;//スクロール速さ（0～1）

	static float quakeTime;//震えの時間

	static VECTOR2 quakeScale;//震えの大きさ

	static void (*gCallback)();//震えの終了時に呼び出す関数、呼出し後に破棄

	static bool isQuakeUp;//揺れの方向がプラス方向か

};
