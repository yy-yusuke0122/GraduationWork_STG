#pragma once

#include <cmath>
#include "dxlib/DxLib.h"
#include "typedef.h"

namespace UrLib {
	inline bool IntToBool(int val) { return val != 0; }
	inline float ToRadian(float _deg) { return  _deg / 180.0f * DX_PI_F; }
	inline float ToDegree(float _rad) { return _rad * 180.0f / DX_PI_F; }

	inline VECTOR3 operator *(const VECTOR3& v, const MATRIX& m) { return VTransform(v, m); }

	inline VECTOR3& operator *=(VECTOR3& v, const MATRIX& m) { return v = VTransform(v, m); }

	inline MATRIX operator *(const MATRIX& m1, const MATRIX& m2) { return MMult(m1, m2); }
	inline MATRIX& operator *=(MATRIX& m1, const MATRIX& m2) { return m1 = MMult(m1, m2); }

	inline float Remainder(const float& f1, const float& f2) { return f1 - (f2 * (int)(f1 / f2)); }

	inline Quaternion operator *(const Quaternion& q1, const Quaternion& q2) 
	{
		Quaternion q;
		q.x = q1.w * q2.x - q1.z * q2.y + q1.y * q2.z + q1.x * q2.w;
		q.y = q1.z * q2.x + q1.w * q2.y - q1.x * q2.z + q1.y * q2.w;
		q.z = -q1.y * q2.x + q1.x * q2.y + q1.w * q2.z + q1.z * q2.w;
		q.w = -q1.x * q2.x - q1.y * q2.y - q1.z * q2.z + q1.w * q2.w;

		return q;
	}

	template<typename T>
	inline bool Clamp(T& val, T min, T max)
	{
		if (min > max) return false;
		else if (val < min) val = min;
		else if (val > max) val = max;
		return true;
	}

	template<typename T>
	inline bool LoopClamp(T& val, T min, T max)
	{
		if (min > max) return false;
		while (val < min) {
			T temp = val - min;
			val = max + temp;
		}
		while (val > max) {
			T temp = val - max;
			val = min + temp;
		}
		return true;
	}

	template<typename T>
	inline bool IsInSideValue(T _val, T _min, T _max) {
		if (_val >= _min && _val < _max) {
			return true;
		}
		else
			return false;
	}

	/// <summary>
	/// ボックスの回転描画
	/// </summary>
	/// <param name="box">描画したいボックス</param>
	/// <param name="Angle">回転角度(ラジアン)</param>
	/// <param name="Color">描画する四角形の色</param>
	/// <param name="FillFlag">四角の中身を塗りつぶすか、のフラグ。TRUEで塗りつぶし、FALSEで塗りつぶさない</param>
	/// <returns>0:成功,-1:失敗</returns>
	inline int DrawRotaBox(AABB2D box, double Angle, unsigned int Color, int FillFlag) {
		VECTOR2 v[4];
		float rad = Angle;
		v[0].x = cos(rad) * box.LeftTop().x - sin(rad) * box.LeftTop().y + box.p.x;
		v[0].y = sin(rad) * box.LeftTop().x + cos(rad) * box.LeftTop().y + box.p.y;
		v[1].x = cos(rad) * box.RightTop().x - sin(rad) * box.RightTop().y + box.p.x;
		v[1].y = sin(rad) * box.RightTop().x + cos(rad) * box.RightTop().y + box.p.y;
		v[2].x = cos(rad) * box.RightBottom().x - sin(rad) * box.RightBottom().y + box.p.x;
		v[2].y = sin(rad) * box.RightBottom().x + cos(rad) * box.RightBottom().y + box.p.y;
		v[3].x = cos(rad) * box.LeftBottom().x - sin(rad) * box.LeftBottom().y + box.p.x;
		v[3].y = sin(rad) * box.LeftBottom().x + cos(rad) * box.LeftBottom().y + box.p.y;

		for (int i = 0; i < 4; ++i) {
			int end = i == 3 ? 0 : i + 1;
			int ret = DrawLine(v[i].x, v[i].y, v[end].x, v[end].y, Color, FillFlag);
			if (ret == -1) {
				return -1;
			}
		}

		return 0;
	}

	/// <summary>
	/// OBB同士の衝突チェック
	/// </summary>
	/// <returns>true:衝突している, false:衝突していない</returns>
	bool ColOBBs(OBB& obb1, OBB& obb2);

	// 分離軸に投影された軸成分から投影線分長を算出
	float LenSegOnSeparateAxis(VECTOR3 Sep, VECTOR3 e1, VECTOR3 e2, VECTOR3 e3 = VECTOR3::zero());
}
using namespace UrLib;