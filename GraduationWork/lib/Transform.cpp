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
    // �����l��0�Ȃ�ΏI��
    if (velocity.Length() == 0.0f) {
        return;
    }

    // �����l�ɖ��C�W������Z
    velocity = velocity * FRICTION_VAL;

    // �����l��0�ɋ߂����0�ɂ��ďI��
    if (velocity.Length() < PRECISION_ERROR) {
        velocity.Clear();
        return;
    }

    // ���W�ɉ��Z
    AddPosition(velocity);
}

void Transform::SetPosition(VECTOR3 _pos)
{
    // �ړ��ʂ��Z�o
    VECTOR3 dif = _pos - position;

    // �����̍��W����
    position = _pos;

    // �ړ������ʂ����q�̍��W�����Z
    for (auto child : gameObject->GetChildren()) {
        child->transform->AddPosition(dif);
    }
}

void Transform::AddPosition(VECTOR2 _add)
{
    // �����̍��W�����Z
    position += _add;

    // �q�̍��W�����Z
    for (auto child : gameObject->GetChildren()) {
        child->transform->AddPosition(_add);
    }
}

void Transform::AddPosition(VECTOR3 _add)
{
    // �����̍��W�����Z
    position += _add;

    // �q�̍��W�����Z
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

    // 2D�̓����蔻��ɉ�]�l�𔽉f
    BoxCollider2D* boxCollider2D = GetComponent<BoxCollider2D>();
    if (boxCollider2D != nullptr) {
        boxCollider2D->rotation += _deg;
    }
}

void Transform::Rotate(VECTOR3 _axis, float _deg)
{
    VECTOR3 vec = VNorm(_axis);

    // �����̌������X�V
    Quaternion::RotatePosition(_axis, &foward, _deg);
    Quaternion::RotatePosition(_axis, &right, _deg);
    Quaternion::RotatePosition(_axis, &up, _deg);

    // �R���C�_�[����]
    BoxCollider* col = GetComponent<BoxCollider>();
    if (col != nullptr) {
        col->Rotate(_axis, _deg);
    }

    // �q�̍��W���X�V
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
