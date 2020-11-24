#include "DirectionMover.h"

void DirectionMover::Start()
{
}

void DirectionMover::Update()
{
	transform->position += VECTOR3::right() * speed * Time::DeltaTime() * MGetRotZ(rad);
}
