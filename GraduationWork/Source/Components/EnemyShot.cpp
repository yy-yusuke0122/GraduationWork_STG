#include "DirectionMover.h"
#include "EnemyShot.h"

namespace
{
	constexpr float SHOT_SPEED = 10.f;
}

void EnemyShot::Start()
{
	direction = AddComponent<DirectionMover>();//�w������ֈړ�
	AddComponent<CircleCollider2D>();//�R���C�_

	direction->speed = SHOT_SPEED;
}

void EnemyShot::SetTargetPos(const VECTOR3& _pos)
{
	VECTOR3 dist = _pos - transform->position;
	direction->rad = atan2f(dist.y, dist.y);
}
