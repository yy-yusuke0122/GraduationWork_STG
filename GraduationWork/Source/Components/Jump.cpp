#include "Jump.h"

Jump::Jump()
{
}

Jump::~Jump()
{
}

void Jump::Start()
{
	power = 100;
	gravity = 25;
	speed = ;
}

void Jump::Update()
{
	VECTOR3 vec;
	vec = VGet(0.0f, 0.0f, 0.0f);
	transform->AddPosition(vec);
	
	(power -= 1) * speed;
	if( )
}
