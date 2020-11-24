#include "Life.h"

Life::Life()
{
	hp = 1.0f;
	max = 1.0f;
}

Life::~Life()
{
}

void Life::Start()
{
}

void Life::Update()
{
}

void Life::Damage(float _damage)
{
	hp -= _damage;
}

void Life::SetHP(float _hp)
{
	hp = _hp;
	Clamp(hp, 0.0f, max);
}

void Life::SetMaxHP(float _max)
{
	max = _max;
	if (max < 0.0f) {
		max = 0.0f;
	}
	if (max < hp) {
		hp = max;
	}
}
