#pragma once
#include "dxlib/DxLib.h"
#include <vector>
#include <math.h>

namespace UrLib {
#define _OX_EPSILON_	0.000001f	// �덷

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

		// ���Z�b�g
		void Clear() {
			x = 0.0f;
			y = 0.0f;
		}

		// �W����
		void Norm() {
			const float len = Length();
			if (len > 0.0f) {
				x /= len;
				y /= len;
			}
		}

		// ��]
		void Rotate(float rad) {
			VECTOR2 v = *this;
			this->x = v.x * cosf(rad) + v.y * -sinf(rad);
			this->y = v.x * sinf(rad) + v.y * cosf(rad);
		}

		// �����֌W�ɂ��邩
		bool IsVertical(const VECTOR2& r) const {
			float d = Dot(r);
			return (-_OX_EPSILON_ < d && d < _OX_EPSILON_);	// �덷�͈͓��Ȃ琂���Ɣ���
		}

		// ���s�֌W�ɂ��邩
		bool IsParallel(const VECTOR2& r) const {
			float d = Cross(r);
			return (-_OX_EPSILON_ < d && d < _OX_EPSILON_);	// �덷�͈͓��Ȃ畽�s�Ɣ���
		}

		// �s�p�֌W��
		bool IsSharpAngle(const VECTOR2& r) const {
			return (Dot(r) >= 0.0f);
		}
	};

	struct Line2D {
		Point2D p;
		VECTOR2 v;		// �����x�N�g��
		Line2D() : p(0.0f, 0.0f), v(1.0f, 0.0f) {}
		Line2D(const Point2D& p, const VECTOR2& v) : p(p), v(v) {}
		~Line2D() {}

		// �_��̍��W���擾
		// �x�N�g���Ɋ|���Z����W��
		Point2D GetPoint(float t) const {
			return p + t * v;
		}
	};

	struct Segment2D : public Line2D {
		Segment2D() {}
		Segment2D(const Point2D& p, const VECTOR2& v) : Line2D(p, v) {}
		Segment2D(const Point2D& p1, const Point2D& p2) : Line2D(p1, p2 - p1) {}

		// �I�_���擾
		Point2D GetEndPoint() const {
			return p + v;
		}
	};

	struct Circle2D {
		Point2D p;
		float r;	// ���a
		Circle2D() : p(0.0f, 0.0f), r(1.0f) {}
		Circle2D(const Point2D& p, float r) : p(p), r(r) {}
		~Circle2D() {}
	};

	struct Capsule2D {
		Segment2D s;
		float r;	// ���a
		Capsule2D() : r(1.0f) {}
		Capsule2D(const Segment2D& s, float r) : s(s), r(r) {}
		Capsule2D(const Point2D& p1, const Point2D& p2, float r) : s(p1, p2), r(r) {}
		~Capsule2D() {}
	};

	struct AABB2D {
		Point2D p;	// ���S�_
		Float2 hl;	// �e���̕ӂ̒����̔���
		AABB2D() {}
		AABB2D(const Point2D& p, const Float2& hl) : p(p), hl(hl) {}

		// �ӂ̒������擾
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
		Point2D p[3];	// ���_���W
		Triangle2D() {}
		~Triangle2D() {}

		// �ӂ̒������擾
		float Len(int i) const {
			// i = 0�͕�p1p2�ȂǓ_pi�̑Εӂ̒���
			return Vec(i).Length();
		}

		// �Ӄx�N�g���i�񐳋K���j���擾
		VECTOR2 Vec(int i) const {
			// i = 0�̓x�N�g��p1p2�ȂǓ_pi�̑Εӂ̕����x�N�g��
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

		// �W����
		void Norm() {
			const float len = Length();
			if (len > 0.0f) {
				x /= len;
				y /= len;
				z /= len;
			}
		}

		// �����֌W�ɂ��邩
		bool IsVertical(const VECTOR3& r) const {
			float d = Dot(r);
			return (-_OX_EPSILON_ < d && d < _OX_EPSILON_);	// �덷�͈͓��Ȃ琂���Ɣ���
		}

		// ���s�֌W�ɂ��邩
		bool IsParallel(const VECTOR3& r) const {
			float d = Cross(r).LengthSq();
			return (-_OX_EPSILON_ < d && d < _OX_EPSILON_);	// �덷�͈͓��Ȃ畽�s�Ɣ���
		}

		// �s�p�֌W��
		bool IsSharpAngle(const VECTOR3& r) const {
			return (Dot(r) >= 0.0f);
		}
	};

	struct Line {
		Point p;
		VECTOR3 v;		// �����x�N�g��
		Line() : p(0.0f, 0.0f, 0.0f), v(1.0f, 0.0f, 0.0f) {}
		Line(const Point& p, const VECTOR3& v) : p(p), v(v) {}
		~Line() {}

		// �_��̍��W���擾
		//  �x�N�g���Ɋ|���Z����W��
		Point GetPoint(float t) const {
			return p + t * v;
		}
	};

	struct Segment : public Line {
		Segment() {}
		Segment(const Point& p, const VECTOR3& v) : Line(p, v) {}
		Segment(const Point& p1, const Point& p2) : Line(p1, p2 - p1) {}

		// �I�_���擾
		Point GetEndPoint() const {
			return p + v;
		}
	};

	struct Sphere {
		Point p;
		float r;	// ���a
		Sphere() : p(0.0f, 0.0f, 0.0f), r(0.5f) {}
		Sphere(const Point& p, float r) : p(p), r(r) {}
		~Sphere() {}
	};

	struct Capsule {
		Segment s;
		float r;	// ���a
		Capsule() : r(0.5f) {}
		Capsule(const Segment& s, float r) : s(s), r(r) {}
		Capsule(const Point& p1, const Point& p2, float r) : s(p1, p2), r(r) {}
		~Capsule() {}
	};

	struct AABB {
		Point p;	// ���S�_
		Float3 hl;	// �e���̕ӂ̒����̔���
		AABB() {}
		AABB(const Point& p, const Float3& hl) : p(p), hl(hl) {}

		// �ӂ̒������擾
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
		/// �x�N�g�����擾
		/// </summary>
		/// <returns>�p�����������x�N�g��</returns>
		VECTOR3 GetVec() const { return VECTOR3(x, y, z); }
	};

	class OBB {
	public:
		OBB();
		~OBB();
		VECTOR3 GetDirect(int elem);	// �w�莲�ԍ��̕����x�N�g�����擾
		float GetLen_W(int elem);		// �w�莲�����̒������擾
		VECTOR3 GetPos_W();				// �ʒu���擾
		void SetPosition(Point pos);	// �ʒu��ݒ�
		void Rotate(VECTOR3 _axis, float _deg);	// OBB����]������
		void SetLength(int elem, float len);	// �w�莲�̒�����ݒ�

	protected:
		Point p;				// �ʒu
		VECTOR3 NormaDirect[3];	// �����x�N�g��
		float Length[3];		// �e�������̒���
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
