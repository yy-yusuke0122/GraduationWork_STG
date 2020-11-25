#include "Character.h"
#include "../Components/Life.h"

Character::Character()
{
	imageRenderer = AddComponent<ImageRenderer>();
	life = AddComponent<Life>();
	circleCollider2D = AddComponent<CircleCollider2D>();
}

Character::~Character()
{
}

void Character::Start()
{
}
