#include "Stage.h"

float Stage::GetY()
{
	return UrLib::Screen::y * 2.f / 3.f;
}

void Stage::Start()
{
	BoxCollider2D* p = AddComponent<BoxCollider2D>();

	float y = UrLib::Screen::y + GetY() / 2.f;

	p->box.p.x = UrLib::Screen::x / 2.f;
	p->box.p.y = y;

	p->box.hl.x = p->box.p.x;
	p->box.hl.y = y - GetY();
}
