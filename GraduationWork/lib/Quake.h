#pragma once

#include "typedef.h"

class Object;

class Quake
{
public:
	Quake() :
		currentTime(0.f), callObj(nullptr), cCallback(nullptr),
		time(1.f), scale(1.f, 1.f), gCallback(nullptr), speed(1.f, 1.f), isPlay(false)
	{
	}

	~Quake()
	{
	}

	void Update();

	/// <summary>
	/// 震わせる
	/// </summary>
	void Play()
	{
		isPlay = true;
	}

	/// <summary>
	/// 震えの終了時に呼び出す関数をセット
	/// 呼出し後に破棄
	/// </summary>
	/// <typeparam name="C">クラス型</typeparam>
	/// <param name="_obj">オブジェクトアドレス</param>
	/// <param name="_call">呼び出す関数</param>
	template<class C>
	void QuakeEndCallback(C* _obj, void (C::* _call)())
	{
		callObj = _obj;
		cCallback = reinterpret_cast<void (Object::*)()> (_call);
	}

	/// <summary>
	/// Playからの経過時間を取得
	/// </summary>
	/// <returns>経過時間</returns>
	float GetTime()const { return currentTime; }

	/// <summary>
	/// Quake中か取得
	/// </summary>
	/// <returns>true：Quake中、false：Play待ち</returns>
	bool IsPlay()const { return isPlay; }

	/// <summary>
	/// コールバックするオブジェクトを取得
	/// </summary>
	/// <returns>呼び出すオブジェクト</returns>
	Object* GetObj()const { return callObj; }

	/// <summary>
	/// コールバックするメソッドを取得
	/// </summary>
	/// <returns>呼び出すメソッド</returns>
	auto GetCallBack() { return cCallback; };

	/// <summary>
	/// Quakeの値を取得
	/// </summary>
	/// <returns>Quake値</returns>
	const VECTOR2& GetValue()const { return value; }

private:
	void EndQuake();

private:
	float currentTime;

	Object* callObj;
	void (Object::* cCallback)();

	VECTOR2 value;

public:
	VECTOR2 center;//中心

	float time;//震えの時間

	VECTOR2 scale;//震えの大きさ

	VECTOR2 speed;//スクロール速さ

	void (*gCallback)();//震えの終了時に呼び出す関数、呼出し後に破棄

private:
	bool isPlay;
};
