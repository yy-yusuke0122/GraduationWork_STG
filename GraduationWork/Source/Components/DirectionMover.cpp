#include "DirectionMover.h"

void DirectionMover::Start()
{
}

void DirectionMover::Update()
{
	transform->position += VECTOR3::right() * speed * Time::DeltaTime() * MGetRotZ(rad);

	printfDx("x = %f\n", transform->position.x);
	printfDx("y = %f\n", transform->position.y);
	printfDx("z = %f\n", transform->position.z);
}
