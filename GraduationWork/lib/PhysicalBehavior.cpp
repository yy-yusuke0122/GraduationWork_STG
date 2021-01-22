#include "PhysicalBehavior.h"
#include "Time.h"
#include "Transform.h"

PhysicalBehavior::PhysicalBehavior() :
    velocity(VECTOR3::zero()), isLanding(false),
    gravityDir(VECTOR3::zero()), gravity(0.0f), useGravity(true),
    friction(0.0f), drag(0.0f)
{
}

PhysicalBehavior::~PhysicalBehavior()
{
}

void PhysicalBehavior::Start()
{
    const SceneOption& s = GetScene()->option;
    gravityDir = s.gravityDir;
    gravity = s.gravity;
    useGravity = s.useGravity;
    friction = s.friction;
    drag = s.drag;
}

void PhysicalBehavior::PostUpdate()
{
    // �V�[���ݒ���擾
    const SceneOption& scene = GetScene()->option;

    // ��������
    if (scene.useGravity && useGravity && !isLanding) {
        velocity += gravityDir * gravity * Time::DeltaTime();
    }

    // ��R���v�Z
    if (isLanding) { // ���n���Ă��鎞
        velocity -= velocity * friction;
    }
    else { // �󒆂ɂ��鎞
        velocity -= velocity * drag;
    }

    // �����l��0�ɋ߂����0�ɂ��ďI��
    if (velocity.Length() < _OX_EPSILON_) {
        velocity.Clear();
        return;
    }

    // ���W�ɉ��Z
    transform->AddPosition(velocity);
}
