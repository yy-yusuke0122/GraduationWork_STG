#include "typedef.h"
#include "Function.h"
#include <cmath>

Quaternion UrLib::Quaternion::Create(VECTOR3 _axis, float _deg)
{
    VECTOR3 vec = VNorm(_axis);
    float rad = ToRadian(_deg);
    Quaternion q;
    q.w = cos(rad / 2.0f);
    q.x = vec.x * sin(rad / 2.0f);
    q.y = vec.y * sin(rad / 2.0f);
    q.z = vec.z * sin(rad / 2.0f);

    return q;
}

VECTOR3 UrLib::Quaternion::RotatePosition(VECTOR3 _axis, VECTOR3 _pos, float _deg)
{
    Quaternion q = Quaternion::Create(_axis, _deg);
    Quaternion r = Quaternion::Create(_axis * -1.0f, _deg);
    Quaternion p;
    p.x = _pos.x;
    p.y = _pos.y;
    p.z = _pos.z;
    p.w = 0.0f;

    Quaternion affter = r * p * q;
    _pos.x = affter.x;
    _pos.y = affter.y;
    _pos.z = affter.z;

    return _pos;
}

Quaternion UrLib::Quaternion::RotatePosition(VECTOR3 _axis, Quaternion _pos, float _deg)
{
    // 角度をRadianに直す
    float rad = ToRadian(_deg);

    // 回転軸と同じベクトルは、ひねるだけ
    if (_axis == _pos.GetVec()) {
        _pos.w += rad;
        LoopClamp(_pos.w, 0.0f, 360.0f);
    }

    // 回転軸を生成し、移動後の座標を算出
    Quaternion q = Quaternion::Create(_axis, _deg);
    Quaternion r = Quaternion::Create(_axis * -1.0f, _deg);
    Quaternion p;
    p.x = _pos.x;
    p.y = _pos.y;
    p.z = _pos.z;
    p.w = 0.0f;

    _pos = r * p * q;

    return _pos;
}

void UrLib::Quaternion::RotatePosition(VECTOR3 _axis, VECTOR3* _pos, float _deg)
{
    Quaternion q = Quaternion::Create(_axis, _deg);
    Quaternion r = Quaternion::Create(_axis * -1.0f, _deg);
    Quaternion p;
    p.x = _pos->x;
    p.y = _pos->y;
    p.z = _pos->z;
    p.w = 0.0f;

    Quaternion affter = r * p * q;
    _pos->x = affter.x;
    _pos->y = affter.y;
    _pos->z = affter.z;
}

void UrLib::Quaternion::RotatePosition(VECTOR3 _axis, Quaternion* _pos, float _deg)
{
    // 角度をRadianに直す
    float rad = ToRadian(_deg);

    // 回転軸と同じベクトルは、ひねるだけ
    if (_axis == _pos->GetVec()) {
        _pos->w += rad;
        LoopClamp(_pos->w, 0.0f, 360.0f);
    }

    // 回転軸を生成し、移動後の座標を算出
    Quaternion q = Quaternion::Create(_axis, _deg);
    Quaternion r = Quaternion::Create(_axis * -1.0f, _deg);
    Quaternion p;
    p.x = _pos->x;
    p.y = _pos->y;
    p.z = _pos->z;
    p.w = 0.0f;

    *_pos = r * p * q;
}

MATRIX UrLib::Quaternion::GetMatrix() const
{
    VECTOR3 sq(x, y, z);
    sq = sq * sq;

    float sqw = w * w;

    float	xy = x * y, xz = x * z, xw = x * w,
        yz = y * z, yw = y * w, zw = z * w;

    MATRIX m = MGetIdent();

    //転置して代入

    m.m[0][0] = sq.x - sq.y - sq.z + sqw;
    m.m[1][0] = 2.f * (xy - zw);
    m.m[2][0] = 2.f * (yw + xz);

    m.m[0][1] = 2.f * (zw + xy);
    m.m[1][1] = -sq.x + sq.y - sq.z + sqw;
    m.m[2][1] = 2.f * (yz - xw);

    m.m[0][2] = 2.f * (xz - yw);
    m.m[1][2] = 2.f * (yz + xw);
    m.m[2][2] = -sq.x - sq.y + sq.z + sqw;

    return m;
}

UrLib::OBB::OBB() : 
    p(VGet(0.0f, 0.0f, 0.0f)), 
    NormaDirect{ VGet(1.0f, 0.0f, 0.0f), VGet(0.0f, 1.0f, 0.0f), VGet(0.0f, 0.0f, 1.0f) },
    Length{ 1.0f, 1.0f, 1.0f }
{
}

UrLib::OBB::~OBB()
{
}

VECTOR3 UrLib::OBB::GetDirect(int elem)
{
    return NormaDirect[elem];
}

float UrLib::OBB::GetLen_W(int elem)
{
    return Length[elem];
}
VECTOR3 UrLib::OBB::GetPos_W()
{
    return p;
}

void UrLib::OBB::SetPosition(Point pos)
{
    p = pos;
}

void UrLib::OBB::Rotate(VECTOR3 _axis, float _deg)
{
    VECTOR3 vec = VNorm(_axis);

    // 各軸を回転
    Quaternion::RotatePosition(_axis, NormaDirect[0], _deg);
    Quaternion::RotatePosition(_axis, NormaDirect[1], _deg);
    Quaternion::RotatePosition(_axis, NormaDirect[2], _deg);
}

void UrLib::OBB::SetLength(int elem, float len)
{
    Length[elem] = len;
}

bool UrLib::ColOBBs(OBB& obb1, OBB& obb2)
{
    // 各方向ベクトルの確保
    // （N***:標準化方向ベクトル）
    VECTOR3 NAe1 = obb1.GetDirect(0), Ae1 = NAe1 * obb1.GetLen_W(0);
    VECTOR3 NAe2 = obb1.GetDirect(1), Ae2 = NAe2 * obb1.GetLen_W(1);
    VECTOR3 NAe3 = obb1.GetDirect(2), Ae3 = NAe3 * obb1.GetLen_W(2);
    VECTOR3 NBe1 = obb2.GetDirect(0), Be1 = NBe1 * obb2.GetLen_W(0);
    VECTOR3 NBe2 = obb2.GetDirect(1), Be2 = NBe2 * obb2.GetLen_W(1);
    VECTOR3 NBe3 = obb2.GetDirect(2), Be3 = NBe3 * obb2.GetLen_W(2);
    VECTOR3 Interval = obb1.GetPos_W() - obb2.GetPos_W();

    // 分離軸 : Ae1
    float rA = VSize(Ae1);
    float rB = LenSegOnSeparateAxis(NAe1, Be1, Be2, Be3);
    float L = fabs(VDot(Interval, NAe1));
    if (L > rA + rB)
        return false; // 衝突していない

     // 分離軸 : Ae2
    rA = VSize(Ae2);
    rB = LenSegOnSeparateAxis(NAe2, Be1, Be2, Be3);
    L = fabs(VDot(Interval, NAe2));
    if (L > rA + rB)
        return false;

    // 分離軸 : Ae3
    rA = VSize(Ae3);
    rB = LenSegOnSeparateAxis(NAe3, Be1, Be2, Be3);
    L = fabs(VDot(Interval, NAe3));
    if (L > rA + rB)
        return false;

    // 分離軸 : Be1
    rA = LenSegOnSeparateAxis(NBe1, Ae1, Ae2, Ae3);
    rB = VSize(Be1);
    L = fabs(VDot(Interval, NBe1));
    if (L > rA + rB)
        return false;

    // 分離軸 : Be2
    rA = LenSegOnSeparateAxis(NBe2, Ae1, Ae2, Ae3);
    rB = VSize(Be2);
    L = fabs(VDot(Interval, NBe2));
    if (L > rA + rB)
        return false;

    // 分離軸 : Be3
    rA = LenSegOnSeparateAxis(NBe3, Ae1, Ae2, Ae3);
    rB = VSize(Be3);
    L = fabs(VDot(Interval, NBe3));
    if (L > rA + rB)
        return false;

    // 分離軸 : C11
    VECTOR3 Cross;
    Cross = VCross(NAe1, NBe1);
    rA = LenSegOnSeparateAxis(Cross, Ae2, Ae3);
    rB = LenSegOnSeparateAxis(Cross, Be2, Be3);
    L = fabs(VDot(Interval, Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C12
    Cross = VCross(NAe1, NBe2);
    rA = LenSegOnSeparateAxis(Cross, Ae2, Ae3);
    rB = LenSegOnSeparateAxis(Cross, Be1, Be3);
    L = fabs(VDot(Interval, Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C13
    Cross = VCross(NAe1, NBe3);
    rA = LenSegOnSeparateAxis(Cross, Ae2, Ae3);
    rB = LenSegOnSeparateAxis(Cross, Be1, Be2);
    L = fabs(VDot(Interval, Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C21
    Cross = VCross(NAe2, NBe1);
    rA = LenSegOnSeparateAxis(Cross, Ae1, Ae3);
    rB = LenSegOnSeparateAxis(Cross, Be2, Be3);
    L = fabs(VDot(Interval, Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C22
    Cross = VCross(NAe2, NBe2);
    rA = LenSegOnSeparateAxis(Cross, Ae1, Ae3);
    rB = LenSegOnSeparateAxis(Cross, Be1, Be3);
    L = fabs(VDot(Interval, Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C23
    Cross = VCross(NAe2, NBe3);
    rA = LenSegOnSeparateAxis(Cross, Ae1, Ae3);
    rB = LenSegOnSeparateAxis(Cross, Be1, Be2);
    L = fabs(VDot(Interval, Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C31
    Cross = VCross(NAe3, NBe1);
    rA = LenSegOnSeparateAxis(Cross, Ae1, Ae2);
    rB = LenSegOnSeparateAxis(Cross, Be2, Be3);
    L = fabs(VDot(Interval, Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C32
    Cross = VCross(NAe3, NBe2);
    rA = LenSegOnSeparateAxis(Cross, Ae1, Ae2);
    rB = LenSegOnSeparateAxis(Cross, Be1, Be3);
    L = fabs(VDot(Interval, Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C33
    Cross = VCross(NAe3, NBe3);
    rA = LenSegOnSeparateAxis(Cross, Ae1, Ae2);
    rB = LenSegOnSeparateAxis(Cross, Be1, Be2);
    L = fabs(VDot(Interval, Cross));
    if (L > rA + rB)
        return false;

    // 分離平面が存在しないので「衝突している」
    return true;
}

float UrLib::LenSegOnSeparateAxis(VECTOR3 Sep, VECTOR3 e1, VECTOR3 e2, VECTOR3 e3)
{
    // 3つの内積の絶対値の和で投影線分長を計算
    // 分離軸Sepは標準化されていること
    float r1 = fabs(VDot(Sep, e1));
    float r2 = fabs(VDot(Sep, e2));
    float r3 = VSize(e3) ? (fabs(VDot(Sep, e3))) : 0.0f;
    return r1 + r2 + r3;
}
