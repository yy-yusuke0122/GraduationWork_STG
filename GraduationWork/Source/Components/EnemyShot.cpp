#include "DirectionMover.h"
#include "EnemyShot.h"

namespace
{
	constexpr float SHOT_SPEED = 10.f;
}

void EnemyShot::Start()
{
	direction = AddComponent<DirectionMover>();//指定方向へ移動
	AddComponent<CircleCollider2D>();//コライダ

	direction->speed = SHOT_SPEED;
}

void EnemyShot::SetTargetPos(const VECTOR3& _pos)
{
	VECTOR3 dist = _pos - transform->position;
	direction->rad = atan2f(dist.y, dist.y);
}
