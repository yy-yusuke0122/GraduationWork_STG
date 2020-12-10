#include "Function.h"
#include "Scroll.h"

VECTOR2 Scroll::scrollValue;

VECTOR2 Scroll::value;//�X�N���[���l

VECTOR2 Scroll::speed(1.f, 1.f);//�X�N���[�����x

void Scroll::Update()
{
	Clamp(speed.x, 0.f, 1.f);
	Clamp(speed.y, 0.f, 1.f);

	VECTOR2 dist = value - scrollValue;

	scrollValue += dist * speed;

}
