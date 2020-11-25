#include "ScreenCollider.h"

void ScreenCollider::Start()
{
	BoxCollider2D* box = AddComponent<BoxCollider2D>();

	using S = UrLib::Screen;

	box->box.p.x = S::x / 2.f;
	box->box.p.y = S::y / 2.f;

	box->box.hl = box->box.p;
}
