#include "ProjectileMoveMent.h"

ProjectileMoveMent::ProjectileMoveMent() :
	direction(VECTOR3::zero()), speed(0.0f)
{
}

ProjectileMoveMent::~ProjectileMoveMent()
{
}

void ProjectileMoveMent::Start()
{
}

void ProjectileMoveMent::Update()
{
	transform->AddPosition(direction * speed);
}
