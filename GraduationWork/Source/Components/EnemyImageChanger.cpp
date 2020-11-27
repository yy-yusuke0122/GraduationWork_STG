#include "../Objects/Player.h"
#include "EnemyImageChanger.h"

void EnemyImageChanger::Start()
{
	image = GetComponent<ImageRenderer>();
}

void EnemyImageChanger::Update()
{
	GameObject* p = FindGameObject("Player");
	if (p != nullptr)
	{
		float x = p->transform->position.x - transform->position.x;
		image->turnXFlag = x > 0.f;
	}
}
