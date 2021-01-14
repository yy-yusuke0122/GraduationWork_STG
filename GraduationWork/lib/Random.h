#pragma once

#include "typedef.h"

class Random
{
private:
	Random()
	{
	}

	~Random()
	{
	}

public:
	/// <summary>
	/// 初期化値セット
	/// </summary>
	/// <returns>true：成功、false：失敗</returns>
	static bool SetSeed(int _seed);

	/// <summary>
	/// 整数ランダム値取得
	/// [0, int最大値]
	/// </summary>
	/// <returns>整数ランダム値</returns>
	static int Get();

	/// <summary>
	/// 整数ランダム値取得
	/// [0, _max)
	/// </summary>
	/// <param name="_max">取得するランダム値の最大値</param>
	/// <returns>整数ランダム値<</returns>
	static int Get(int _max);

	/// <summary>
	/// 整数ランダム値取得
	/// [_min, _max)
	/// </summary>
	/// <param name="_min">取得するランダム値の最小値</param>
	/// <param name="_max">取得するランダム値の最大値</param>
	/// <returns>整数ランダム値</returns>
	static int Get(int _min, int _max);

	/// <summary>
	/// 浮動小数点数ランダム値取得
	/// [0, 1)
	/// </summary>
	/// <returns>浮動小数点数ランダム値</returns>
	static float GetF();

	/// <summary>
	/// 浮動小数点数ランダム値取得
	/// [0, _max)
	/// </summary>
	/// <param name="_max">取得するランダム値の最大値</param>
	/// <returns>浮動小数点数ランダム値</returns>
	static float GetF(float _max);

	/// <summary>
	/// 浮動小数点数ランダム値取得
	/// [_min, _max)
	/// </summary>
	/// <param name="_min">取得するランダム値の最小値</param>
	/// <param name="_max">取得するランダム値の最大値</param>
	/// <returns>浮動小数点数ランダム値</returns>
	static float GetF(float _min, float _max);

	/// <summary>
	/// ランダム整数色取得
	/// </summary>
	/// <returns>ランダム整数色</returns>
	static unsigned Color();

	/// <summary>
	/// ランダム実数色取得
	/// </summary>
	/// <returns>ランダム実数色</returns>
	static COLOR_F ColorF();

	/// <summary>
	/// ランダム2次元ベクトル取得
	/// [0, _max)
	/// </summary>
	/// <param name="_max">取得するランダム値の最大値</param>
	/// <returns>ランダム2次元ベクトル</returns>
	static VECTOR2 Vec2(const VECTOR2& _max);

	/// <summary>
	/// ランダム2次元ベクトル取得
	/// </summary>
	/// <param name="_min">取得するランダム値の最小値</param>
	/// <param name="_max">取得するランダム値の最大値</param>
	/// <returns>ランダム2次元ベクトル</returns>
	static VECTOR2 Vec2(const VECTOR2& _min, const VECTOR2& _max);

	/// <summary>
	/// ランダム3次元ベクトル取得
	/// [0, _max)
	/// </summary>
	/// <param name="_max">取得するランダム値の最大値</param>
	/// <returns>ランダム3次元ベクトル</returns>
	static VECTOR3 Vec3(const VECTOR3& _max);

	/// <summary>
	/// ランダム3次元ベクトル取得
	/// </summary>
	/// <param name="_min">取得するランダム値の最小値</param>
	/// <param name="_max">取得するランダム値の最大値</param>
	/// <returns>ランダム3次元ベクトル</returns>
	static VECTOR3 Vec3(const VECTOR3& _min, const VECTOR3& _max);

	/// <summary>
	/// ランダムクォータニオン取得
	/// </summary>
	/// <returns>ランダムクォータニオン</returns>
	static Quaternion Rotation();

	/// <summary>
	/// 単位円内の一点を取得
	/// </summary>
	/// <returns>単位円内の一点</returns>
	static VECTOR2 InCircle();

	/// <summary>
	/// 単位円上の一点を取得
	/// </summary>
	/// <returns>単位円上の一点</returns>
	static VECTOR2 OnCircle();

	/// <summary>
	/// 単位球内の一点を取得
	/// </summary>
	/// <returns>単位球内の一点</returns>
	static VECTOR3 InSphere();

	/// <summary>
	/// 単位球上の一点を取得
	/// </summary>
	/// <returns>単位球上の一点</returns>
	static VECTOR3 OnSphere();

};
