#include <cmath>
#include "Random.h"
#include "dxlib/DxLib.h"
#include "Function.h"

bool Random::SetSeed(int _seed)
{
    return SRand(_seed);
}

int Random::Get()
{
    return GetRand(INT_MAX);
}

int Random::Get(int _max)
{
    return GetRand(_max - 1);
}

int Random::Get(int _min, int _max)
{
    int random = Get(_max - _min);
    return random + _min;
}

float Random::GetF()
{
    int random = (Get() & 0x007fffff)|0x3f800000;//0 0000000 01111111 11111111 11111111
    return *reinterpret_cast<float*>(&random) - 1.f;
}

float Random::GetF(float _max)
{
    return GetF() * _max;
}

float Random::GetF(float _min, float _max)
{
    return GetF(_max - _min) + _min;
}

unsigned Random::Color()
{
    return GetColor(Get(255), Get(255), Get(255));
}

COLOR_F Random::ColorF()
{
    return GetColorF(GetF(), GetF(), GetF(), GetF());
}

VECTOR2 Random::Vec2(const VECTOR2& _max)
{
    return VECTOR2(GetF(_max.x), GetF(_max.y));
}

VECTOR2 Random::Vec2(const VECTOR2& _min, const VECTOR2& _max)
{
    return VECTOR2(GetF(_min.x, _max.x), GetF(_min.y, _max.y));
}

VECTOR3 Random::Vec3(const VECTOR3& _max)
{
    return VECTOR3(GetF(_max.x), GetF(_max.y), GetF(_max.z));
}

VECTOR3 Random::Vec3(const VECTOR3& _min, const VECTOR3& _max)
{
    return VECTOR3(GetF(_min.x, _max.x), GetF(_min.y, _max.y), GetF(_min.z, _max.z));
}

Quaternion Random::Rotation()
{
    return Quaternion::Create(Vec3(VGet(1.f, 1.f, 1.f)), GetF(360.f));
}

VECTOR2 Random::InCircle()
{
    return OnCircle() * GetF();
}

VECTOR2 Random::OnCircle()
{
    float rad = GetF(DX_TWO_PI_F);
    return VECTOR2(cosf(rad), sinf(rad));
}

VECTOR3 Random::InSphere()
{
    return OnSphere() * GetF();
}

VECTOR3 Random::OnSphere()
{
    return Rotation().GetVec();
}
