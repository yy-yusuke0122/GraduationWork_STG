#pragma once
#include "dxlib/DxLib.h"
#include <vector>
#include <math.h>

namespace UrLib {
#define _OX_EPSILON_	0.000001f	// 誤差

	typedef struct tagFloat2 {
		float x, y;
		tagFloat2() : x(0.0f), y(0.0f) {}
		tagFloat2(float _x, float _y) : x(_x), y(_y) {}
		~tagFloat2() {}
		
		tagFloat2 operator +(const tagFloat2& r) const {
			return tagFloat2(x + r.x, y + r.y);
		}

		tagFloat2 operator -(const tagFloat2& r) const {
			return tagFloat2(x - r.x, y - r.y);
		}

		tagFloat2 operator -() const {
			return tagFloat2(x * -1.0f, y * -1.0f);
		}

		tagFloat2 operator *(const tagFloat2& r) const {
			return tagFloat2(x * r.x, y * r.y);
		}

		tagFloat2 operator /(const tagFloat2& r) const {
			return tagFloat2(x / r.x, y / r.y);
		}

		tagFloat2 operator *(float r) const {
			return tagFloat2(x * r, y * r);
		}

		tagFloat2 operator /(float r) const {
			return tagFloat2(x / r, y / r);
		}

		friend tagFloat2 operator *(float l, const tagFloat2& r) {
			return tagFloat2(r.x * l, r.y * l);
		}

		friend tagFloat2 operator /(float l, const tagFloat2& r) {
			return tagFloat2(r.x / l, r.y / l);
		}

		bool operator ==(const tagFloat2& r) {
			return tagFloat2(*this - r).Length() == 0.0f;
		}

		bool operator !=(const tagFloat2& r) {
			return tagFloat2(*this - r).Length() > 0.0f;
		}

		tagFloat2& operator +=(const tagFloat2& v) {
			x = x + v.x;
			y = y + v.y;
			return *this;
		}

		tagFloat2& operator -=(const tagFloat2& v) {
			x = x - v.x;
			y = y - v.y;
			return *this;
		}

		float Dot(const tagFloat2& r) const {
			return x * r.x + y * r.y;
		}

		float Cross(const tagFloat2& r) const {
			return x * r.y - y * r.x;
		}

		float Length() const {
			return sqrtf(LengthSq());
		}

		float LengthSq() const {
			return x * x + y * y;
		}

		void Norm() {
			const float len = Length();
			if (len > 0.0f) {
				x /= len;
				y /= len;
			}
		}

		tagFloat2 GetNorm() const {
			const float len = Length();
			if (len > 0.0f) {
				return tagFloat2(x / len, y / len);
			}
			return tagFloat2(0.0f, 0.0f);
		}
	} Float2, Point2D;

	struct VECTOR2 : public tagFloat2 {
		VECTOR2() {}
		VECTOR2(float _x, float _y) : tagFloat2(_x, _y) {}
		VECTOR2(const tagFloat2& _r) : tagFloat2(_r) {}

		static VECTOR2 zero() { return VECTOR2(); }
		static VECTOR2 one() { return VECTOR2(1.0f, 1.0f); }
		static VECTOR2 up() { return VECTOR2(0.0f, -1.0f); }
		static VECTOR2 right() { return VECTOR2(1.0f, 0.0f); }

		operator VECTOR() const { return VGet(x, y, 0.0f); }

		VECTOR2& operator =(const Float2& r) {
			x = r.x;
			y = r.y;
			return *this;
		}

		VECTOR2 operator +(const VECTOR2& r) const {
			return VECTOR2(x + r.x, y + r.y);
		}

		VECTOR2 operator -(const VECTOR2& r) const {
			return VECTOR2(x - r.x, y - r.y);
		}

		VECTOR2 operator -() const {
			return VECTOR2(x * -1.0f, y * -1.0f);
		}

		VECTOR2 operator *(const VECTOR2& r) const {
			return VECTOR2(x * r.x, y * r.y);
		}

		VECTOR2 operator /(const VECTOR2& r) const {
			return VECTOR2(x / r.x, y / r.y);
		}

		VECTOR2 operator *(float r) const {
			return VECTOR2(x * r, y * r);
		}

		VECTOR2 operator /(float r) const {
			return VECTOR2(x / r, y / r);
		}

		friend VECTOR2 operator *(float l, const VECTOR2& r) {
			return VECTOR2(r.x * l, r.y * l);
		}

		friend VECTOR2 operator /(float l, const VECTOR2& r) {
			return VECTOR2(r.x / l, r.y / l);
		}

		bool operator ==(const VECTOR2& r) {
			return VECTOR2(*this - r).Length() == 0.0f;
		}

		bool operator !=(const VECTOR2& r) {
			return VECTOR2(*this - r).Length() > 0.0f;
		}

		VECTOR2& operator +=(const VECTOR2& v) {
			x = x + v.x;
			y = y + v.y;
			return *this;
		}

		VECTOR2& operator -=(const VECTOR2& v) {
			x = x - v.x;
			y = y - v.y;
			return *this;
		}

		// リセット
		void Clear() {
			x = 0.0f;
			y = 0.0f;
		}

		// 標準化
		void Norm() {
			const float len = Length();
			if (len > 0.0f) {
				x /= len;
				y /= len;
			}
		}

		// 回転
		void Rotate(float rad) {
			VECTOR2 v = *this;
			this->x = v.x * cosf(rad) + v.y * -sinf(rad);
			this->y = v.x * sinf(rad) + v.y * cosf(rad);
		}

		// 垂直関係にあるか
		bool IsVertical(const VECTOR2& r) const {
			float d = Dot(r);
			return (-_OX_EPSILON_ < d && d < _OX_EPSILON_);	// 誤差範囲内なら垂直と判定
		}

		// 平行関係にあるか
		bool IsParallel(const VECTOR2& r) const {
			float d = Cross(r);
			return (-_OX_EPSILON_ < d && d < _OX_EPSILON_);	// 誤差範囲内なら平行と判定
		}

		// 鋭角関係か
		bool IsSharpAngle(const VECTOR2& r) const {
			return (Dot(r) >= 0.0f);
		}
	};

	struct Line2D {
		Point2D p;
		VECTOR2 v;		// 方向ベクトル
		Line2D() : p(0.0f, 0.0f), v(1.0f, 0.0f) {}
		Line2D(const Point2D& p, const VECTOR2& v) : p(p), v(v) {}
		~Line2D() {}

		// 点上の座標を取得
		// ベクトルに掛け算する係数
		Point2D GetPoint(float t) const {
			return p + t * v;
		}
	};

	struct Segment2D : public Line2D {
		Segment2D() {}
		Segment2D(const Point2D& p, const VECTOR2& v) : Line2D(p, v) {}
		Segment2D(const Point2D& p1, const Point2D& p2) : Line2D(p1, p2 - p1) {}

		// 終点を取得
		Point2D GetEndPoint() const {
			return p + v;
		}
	};

	struct Circle2D {
		Point2D p;
		float r;	// 半径
		Circle2D() : p(0.0f, 0.0f), r(1.0f) {}
		Circle2D(const Point2D& p, float r) : p(p), r(r) {}
		~Circle2D() {}
	};

	struct Capsule2D {
		Segment2D s;
		float r;	// 半径
		Capsule2D() : r(1.0f) {}
		Capsule2D(const Segment2D& s, float r) : s(s), r(r) {}
		Capsule2D(const Point2D& p1, const Point2D& p2, float r) : s(p1, p2), r(r) {}
		~Capsule2D() {}
	};

	struct AABB2D {
		Point2D p;	// 中心点
		Float2 hl;	// 各軸の辺の長さの半分
		AABB2D() {}
		AABB2D(const Point2D& p, const Float2& hl) : p(p), hl(hl) {}

		// 辺の長さを取得
		float LenX() const { return hl.x * 2.0f; };
		float LenY() const { return hl.y * 2.0f; };
		float Len(int i) {
			return *((&hl.x) + i) * 2.0f;
		}

		Point2D LeftTop() const { return Point2D(-hl.x, hl.y); }
		Point2D LeftBottom() const { return Point2D(-hl.x, -hl.y); }
		Point2D RightTop() const { return Point2D(hl.x, hl.y); }
		Point2D RightBottom() const { return Point2D(hl.x, -hl.y); }
	};

	struct Triangle2D {
		Point2D p[3];	// 頂点座標
		Triangle2D() {}
		~Triangle2D() {}

		// 辺の長さを取得
		float Len(int i) const {
			// i = 0は辺p1p2など点piの対辺の長さ
			return Vec(i).Length();
		}

		// 辺ベクトル（非正規化）を取得
		VECTOR2 Vec(int i) const {
			// i = 0はベクトルp1p2など点piの対辺の方向ベクトル
			// i = 0 :  p1p2
			// i = 1 :  p2p0
			// i = 2 :  p0p1
			int idx[] = { 1, 2, 0, 1 };
			return p[idx[i + 1]] - p[idx[i]];
		}
	};

	typedef struct tagFloat3 {
		float x, y, z;
		tagFloat3() : x(0.0f), y(0.0f), z(0.0f) {}
		tagFloat3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
		tagFloat3(VECTOR v) : x(v.x), y(v.y), z(v.z) {}
		~tagFloat3() {}
		
		tagFloat3 operator +(const tagFloat3& r) const {
			return tagFloat3(x + r.x, y + r.y, z + r.z);
		}

		tagFloat3 operator +(const tagFloat2& r) const {
			return tagFloat3(x + r.x, y + r.y, z);
		}

		tagFloat3 operator -(const tagFloat3& r) const {
			return tagFloat3(x - r.x, y - r.y, z - r.z);
		}

		tagFloat3 operator -() const {
			return tagFloat3(x * -1.0f, y * -1.0f, z * -1.0f);
		}

		tagFloat3 operator *(const tagFloat3& r) const {
			return tagFloat3(x * r.x, y * r.y, z * r.z);
		}

		tagFloat3 operator /(const tagFloat3& r) const {
			return tagFloat3(x / r.x, y / r.y, z / r.z);
		}

		tagFloat3 operator *(float r) const {
			return tagFloat3(x * r, y * r, z * r);
		}

		tagFloat3 operator /(float r) const {
			return tagFloat3(x / r, y / r, z / r);
		}

		friend tagFloat3 operator *(float l, const tagFloat3& r) {
			return tagFloat3(r.x * l, r.y * l, r.z * l);
		}

		friend tagFloat3 operator /(float l, const tagFloat3& r) {
			return tagFloat3(r.x / l, r.y / l, r.z / l);
		}

		bool operator ==(const tagFloat3& r) {
			return tagFloat3(*this - r).Length() == 0.0f;
		}

		bool operator !=(const tagFloat3& r) {
			return tagFloat3(*this - r).Length() > 0.0f;
		}

		float Dot(const tagFloat3& r) const {
			return x * r.x + y * r.y + z * r.z;
		}

		tagFloat3 Cross(const tagFloat3& r) const {
			return tagFloat3(y * r.z - z * r.y, z * r.x - x * r.z, x * r.y - y * r.x);
		}

		float Length() const {
			return sqrtf(LengthSq());
		}

		float LengthSq() const {
			return x * x + y * y + z * z;
		}

		void Norm() {
			const float len = Length();
			if (len > 0.0f) {
				x /= len;
				y /= len;
				z /= len;
			}
		}

		tagFloat3 GetNorm() const {
			const float len = Length();
			if (len > 0.0f) {
				return tagFloat3(x / len, y / len, z / len);
			}
			return tagFloat3(0.0f, 0.0f, 0.0f);
		}
	} Float3, Point;

	struct VECTOR3 : public tagFloat3 {
		VECTOR3() {}
		VECTOR3(float _x, float _y, float _z) : tagFloat3(_x, _y, _z) {}
		VECTOR3(tagFloat3 f) : tagFloat3(f) {}
		VECTOR3(VECTOR2 _v) : tagFloat3(_v.x, _v.y, 0.0f) {}
		VECTOR3(VECTOR v) : tagFloat3(v) {}
		static VECTOR3 zero() { return VECTOR3(); }
		static VECTOR3 one() { return VECTOR3(1.0f, 1.0f, 1.0f); }
		static VECTOR3 up() { return VECTOR3(0.0f, 1.0f, 0.0f); }
		static VECTOR3 right() { return VECTOR3(1.0f, 0.0f, 0.0f); }
		static VECTOR3 foward() { return VECTOR3(0.0f, 0.0f, 1.0f); }
		void Clear() { x = 0.0f, y = 0.0f, z = 0.0f; }
		VECTOR3& operator =(const VECTOR& _v) { x = _v.x, y = _v.y, z = _v.z; return *this; }
		operator VECTOR() const { return VGet(x, y, z); }

		VECTOR3& operator =(const Float3& r) {
			x = r.x;
			y = r.y;
			z = r.z;
			return *this;
		}

		VECTOR3 operator +(const VECTOR2& r) const {
			return VECTOR3(x + r.x, y + r.y, z);
		}

		VECTOR3 operator +(const VECTOR3& r) const {
			return VECTOR3(x + r.x, y + r.y, z + r.z);
		}

		VECTOR3 operator -(const VECTOR2& r) const {
			return VECTOR3(x - r.x, y - r.y, z);
		}

		VECTOR3 operator -(const VECTOR3& r) const {
			return VECTOR3(x - r.x, y - r.y, z - r.z);
		}

		VECTOR3 operator -() const {
			return VECTOR3(x * -1.0f, y * -1.0f, z * -1.0f);
		}

		VECTOR3 operator *(const VECTOR3& r) const {
			return VECTOR3(x * r.x, y * r.y, z * r.z);
		}

		VECTOR3 operator /(const VECTOR3& r) const {
			return VECTOR3(x / r.x, y / r.y, z / r.z);
		}

		VECTOR3 operator *(float r) const {
			return VECTOR3(x * r, y * r, z * r);
		}

		VECTOR3 operator /(float r) const {
			return VECTOR3(x / r, y / r, z / r);
		}

		friend VECTOR3 operator *(float l, const VECTOR3& r) {
			return VECTOR3(r.x * l, r.y * l, r.z * l);
		}

		friend VECTOR3 operator /(float l, const VECTOR3& r) {
			return VECTOR3(r.x / l, r.y / l, r.z / l);
		}

		bool operator ==(const VECTOR3& r) {
			return VECTOR3(*this - r).Length() == 0.0f;
		}

		bool operator !=(const VECTOR3& r) {
			return VECTOR3(*this - r).Length() > 0.0f;
		}

		VECTOR3& operator +=(const VECTOR2& v) { 
			x = x + v.x;
			y = y + v.y;
			return *this;
		}

		VECTOR3& operator +=(const VECTOR3& v) {
			x = x + v.x;
			y = y + v.y;
			z = z + v.z;
			return *this;
		}

		VECTOR3& operator -=(const VECTOR2& v) {
			x = x - v.x;
			y = y - v.y;
			return *this;
		}

		VECTOR3& operator -=(const VECTOR3& v) {
			x = x - v.x;
			y = y - v.y;
			z = z - v.z;
			return *this;
		}

		// 標準化
		void Norm() {
			const float len = Length();
			if (len > 0.0f) {
				x /= len;
				y /= len;
				z /= len;
			}
		}

		// 垂直関係にあるか
		bool IsVertical(const VECTOR3& r) const {
			float d = Dot(r);
			return (-_OX_EPSILON_ < d && d < _OX_EPSILON_);	// 誤差範囲内なら垂直と判定
		}

		// 平行関係にあるか
		bool IsParallel(const VECTOR3& r) const {
			float d = Cross(r).LengthSq();
			return (-_OX_EPSILON_ < d && d < _OX_EPSILON_);	// 誤差範囲内なら平行と判定
		}

		// 鋭角関係か
		bool IsSharpAngle(const VECTOR3& r) const {
			return (Dot(r) >= 0.0f);
		}
	};

	struct Line {
		Point p;
		VECTOR3 v;		// 方向ベクトル
		Line() : p(0.0f, 0.0f, 0.0f), v(1.0f, 0.0f, 0.0f) {}
		Line(const Point& p, const VECTOR3& v) : p(p), v(v) {}
		~Line() {}

		// 点上の座標を取得
		//  ベクトルに掛け算する係数
		Point GetPoint(float t) const {
			return p + t * v;
		}
	};

	struct Segment : public Line {
		Segment() {}
		Segment(const Point& p, const VECTOR3& v) : Line(p, v) {}
		Segment(const Point& p1, const Point& p2) : Line(p1, p2 - p1) {}

		// 終点を取得
		Point GetEndPoint() const {
			return p + v;
		}
	};

	struct Sphere {
		Point p;
		float r;	// 半径
		Sphere() : p(0.0f, 0.0f, 0.0f), r(0.5f) {}
		Sphere(const Point& p, float r) : p(p), r(r) {}
		~Sphere() {}
	};

	struct Capsule {
		Segment s;
		float r;	// 半径
		Capsule() : r(0.5f) {}
		Capsule(const Segment& s, float r) : s(s), r(r) {}
		Capsule(const Point& p1, const Point& p2, float r) : s(p1, p2), r(r) {}
		~Capsule() {}
	};

	struct AABB {
		Point p;	// 中心点
		Float3 hl;	// 各軸の辺の長さの半分
		AABB() {}
		AABB(const Point& p, const Float3& hl) : p(p), hl(hl) {}

		// 辺の長さを取得
		float LenX() const { return hl.x * 2.0f; };
		float LenY() const { return hl.y * 2.0f; };
		float LenZ() const { return hl.z * 2.0f; };
		float Len(int i) {
			return *((&hl.x) + i) * 2.0f;
		}
	};

	class Quaternion {
	public:
		Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
		Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
		float x, y, z, w;
		static Quaternion Create(VECTOR3 _axis, float _deg);
		static VECTOR3 RotatePosition(VECTOR3 _axis, VECTOR3 _pos, float _deg);
		static Quaternion RotatePosition(VECTOR3 _axis, Quaternion _pos, float _deg);
		static void RotatePosition(VECTOR3 _axis, VECTOR3* _pos, float _deg);
		static void RotatePosition(VECTOR3 _axis, Quaternion* _pos, float _deg);

		Quaternion operator*(const Quaternion& _q) {
			Quaternion q;

			q.x = w * _q.x - z * _q.y + y * _q.z + x * _q.w;
			q.y = z * _q.x + w * _q.y - x * _q.z + y * _q.w;
			q.z = -y * _q.x + x * _q.y + w * _q.z + z * _q.w;
			q.w = -x * _q.x - y * _q.y - z * _q.z + w * _q.w;

			return q;
		}

		MATRIX GetMatrix() const;

		/// <summary>
		/// ベクトルを取得
		/// </summary>
		/// <returns>姿勢を除いたベクトル</returns>
		VECTOR3 GetVec() const { return VECTOR3(x, y, z); }
	};

	class OBB {
	public:
		OBB();
		~OBB();
		VECTOR3 GetDirect(int elem);	// 指定軸番号の方向ベクトルを取得
		float GetLen_W(int elem);		// 指定軸方向の長さを取得
		VECTOR3 GetPos_W();				// 位置を取得
		void SetPosition(Point pos);	// 位置を設定
		void Rotate(VECTOR3 _axis, float _deg);	// OBBを回転させる
		void SetLength(int elem, float len);	// 指定軸の長さを設定

	protected:
		Point p;				// 位置
		VECTOR3 NormaDirect[3];	// 方向ベクトル
		float Length[3];		// 各軸方向の長さ
	};


	inline VECTOR2& operator +=(VECTOR2&v1, const VECTOR3& v2)
	{
		v1.x = v1.x + v2.x;
		v1.y = v1.y + v2.y;
		return v1;
	}

	inline VECTOR2& operator -=(VECTOR2& v1, const VECTOR3& v2) {
		v1.x = v1.x - v2.x;
		v1.y = v1.y - v2.y;
		return v1;
	}
}
using namespace UrLib;
