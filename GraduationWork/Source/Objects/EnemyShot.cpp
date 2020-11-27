#include "../Components/DirectionMover.h"
#include "../Components/ScreenOut.h"
#include "../Components/DamageToPlayer.h"
#include "EnemyShot.h"

namespace
{
	constexpr float SHOT_SPEED = 500.f;
}

void EnemyShot::Start()
{
	image = AddComponent<ImageRenderer>();
	image->SetImage("Media/EnemyBullet.png");//画像

	CircleCollider2D* collider = AddComponent<CircleCollider2D>();//コライダ
	collider->circle.r = (image->GetSizeX() + image->GetSizeY()) / 4.f;

	direction = AddComponent<DirectionMover>();//指定方向へ移動
	AddComponent<ScreenOut>();

	AddComponent<DamageToPlayer>();//プレイヤーにダメージを与える
}

void EnemyShot::SetTargetPos(const VECTOR3& _pos)
{
	VECTOR3 dist = _pos - transform->position;
	direction->rad = atan2f(dist.y, dist.x);

	direction->speed = SHOT_SPEED;

	image->rotation = ToDegree(direction->rad);
}
