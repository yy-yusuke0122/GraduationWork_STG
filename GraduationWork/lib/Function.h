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

	template<typename T>
	inline void ReplaceValue(T& _a, T& _b)
	{
		T tmp = _b;
		_b = _a;
		_a = tmp;
	}

	template<typename T>
	inline void Clamp(T& _val, T _min, T _max)
	{
		if (_val < _min) _val = _min;
		else if (_val > _max) _val = _max;
	}

	template<typename T>
	inline bool LoopClamp(T& _val, T _min, T _max)
	{
		if (_min > _max || _min == _max) return false;

		T sub = _max - _min;

		if (_val < _min) {
			T over = _val - _min;
			int include = static_cast<int>(over / sub);
			_val = _max - (over - (include * sub));
		}
		else if (_val >= _max) {
			T over = _val - _max;
			int include = static_cast<int>(over / sub);
			_val = _min + (over - (include * sub));
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
		float rad = static_cast<float>(Angle);
		v[0].x = cosf(rad) * box.LeftTop().x - sinf(rad) * box.LeftTop().y + box.p.x;
		v[0].y = sinf(rad) * box.LeftTop().x + cosf(rad) * box.LeftTop().y + box.p.y;
		v[1].x = cosf(rad) * box.RightTop().x - sinf(rad) * box.RightTop().y + box.p.x;
		v[1].y = sinf(rad) * box.RightTop().x + cosf(rad) * box.RightTop().y + box.p.y;
		v[2].x = cosf(rad) * box.RightBottom().x - sinf(rad) * box.RightBottom().y + box.p.x;
		v[2].y = sinf(rad) * box.RightBottom().x + cosf(rad) * box.RightBottom().y + box.p.y;
		v[3].x = cosf(rad) * box.LeftBottom().x - sinf(rad) * box.LeftBottom().y + box.p.x;
		v[3].y = sinf(rad) * box.LeftBottom().x + cosf(rad) * box.LeftBottom().y + box.p.y;

		for (int i = 0; i < 4; ++i) {
			int end = i == 3 ? 0 : i + 1;
			int ret = DrawLine(static_cast<int>(v[i].x), static_cast<int>(v[i].y),
				static_cast<int>(v[end].x), static_cast<int>(v[end].y), Color, FillFlag);
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