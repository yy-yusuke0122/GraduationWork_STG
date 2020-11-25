#include "../Components/DirectionMover.h"
#include "../Components/ScreenOut.h"
#include "EnemyShot.h"

namespace
{
	constexpr float SHOT_SPEED = 500.f;
}

void EnemyShot::Start()
{
	direction = AddComponent<DirectionMover>();//�w������ֈړ�
	AddComponent<CircleCollider2D>();//�R���C�_
	AddComponent<ImageRenderer>()->SetImage("Media/EnemyBullet.png");//�摜
	AddComponent<ScreenOut>();
}

void EnemyShot::SetTargetPos(const VECTOR3& _pos)
{
	VECTOR3 dist = _pos - transform->position;
	direction->rad = atan2f(dist.y, dist.x);

	direction->speed = SHOT_SPEED;
}
