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
    // シーン設定を取得
    const SceneOption& scene = GetScene()->option;

    // 落下処理
    if (scene.useGravity && useGravity && !isLanding) {
        velocity += gravityDir * gravity * Time::DeltaTime();
    }

    // 抵抗を計算
    if (isLanding) { // 着地している時
        velocity -= velocity * friction;
    }
    else { // 空中にいる時
        velocity -= velocity * drag;
    }

    // 加速値が0に近ければ0にして終了
    if (velocity.Length() < _OX_EPSILON_) {
        velocity.Clear();
        return;
    }

    // 座標に加算
    transform->AddPosition(velocity);
}
