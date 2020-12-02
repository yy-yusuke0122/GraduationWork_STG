#include "Transform.h"
#include "Function.h"
#include "BoxCollider.h"
#include "BoxCollider2D.h"
#include "CircleCollider2D.h"
#include "SphereCollider.h"

namespace {
    const float FRICTION_VAL = 0.9f;
    const float PRECISION_ERROR = 0.00001f;
}

Transform::Transform() : 
    position(VECTOR3::zero()), scale(VECTOR3::one()),
    velocity(VECTOR3::zero()), foward(0.0f, 0.0f, 1.0f, 0.0f), right(1.0f, 0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f, 0.0f)
{
}

Transform::~Transform()
{
}

void Transform::Start()
{
}

void Transform::Update()
{
}

void Transform::UpdatePysics()
{
    // 加速値が0ならば終了
    if (velocity.Length() == 0.0f) {
        return;
    }

    // 加速値に摩擦係数を乗算
    velocity = velocity * FRICTION_VAL;

    // 加速値が0に近ければ0にして終了
    if (velocity.Length() < PRECISION_ERROR) {
        velocity.Clear();
        return;
    }

    // 座標に加算
    AddPosition(velocity);
}

void Transform::SetPosition(VECTOR3 _pos)
{
    // 移動量を算出
    VECTOR3 dif = _pos - position;

    // 自分の座標を代入
    position = _pos;

    // 移動した量だけ子の座標を加算
    for (auto child : gameObject->GetChildren()) {
        child->transform->AddPosition(dif);
    }
}

void Transform::AddPosition(VECTOR2 _add)
{
    // 自分の座標を加算
    position += _add;

    // 子の座標を加算
    for (auto child : gameObject->GetChildren()) {
        child->transform->AddPosition(_add);
    }
}

void Transform::AddPosition(VECTOR3 _add)
{
    // 自分の座標を加算
    position += _add;

    // 子の座標を加算
    for (auto child : gameObject->GetChildren()) {
        child->transform->AddPosition(_add);
    }
}

void Transform::AxisRotateX(float _deg)
{
    VECTOR3 vec = { 1.0f, 0.0f, 0.0f };
    Rotate(vec, _deg);
}

void Transform::AxisRotateY(float _deg)
{
    VECTOR3 vec = { 0.0f, 1.0f, 0.0f };
    Rotate(vec, _deg);
}

void Transform::AxisRotateZ(float _deg)
{
    VECTOR3 vec = { 0.0f, 0.0f, 1.0f };
    Rotate(vec, _deg);

    // 2Dの当たり判定に回転値を反映
    BoxCollider2D* boxCollider2D = GetComponent<BoxCollider2D>();
    if (boxCollider2D != nullptr) {
        boxCollider2D->rotation += _deg;
    }
}

void Transform::Rotate(VECTOR3 _axis, float _deg)
{
    VECTOR3 vec = VNorm(_axis);

    // 自分の向きを更新
    Quaternion::RotatePosition(_axis, &foward, _deg);
    Quaternion::RotatePosition(_axis, &right, _deg);
    Quaternion::RotatePosition(_axis, &up, _deg);

    // コライダーを回転
    BoxCollider* col = GetComponent<BoxCollider>();
    if (col != nullptr) {
        col->Rotate(_axis, _deg);
    }

    // 子の座標を更新
    for (auto child : gameObject->GetChildren()) {
        VECTOR3 dif = child->transform->position - position;
        Quaternion::RotatePosition(_axis, dif, _deg);
        child->transform->SetPosition(dif + position);
        child->transform->Rotate(_axis, _deg);
    }
}

VECTOR3 Transform::GetForward() const
{
    return foward.GetVec();
}

VECTOR3 Transform::GetRight() const
{
    return right.GetVec();
}

VECTOR3 Transform::GetUp() const
{
    return up.GetVec();
}
