#include "Scroll.h"

VECTOR2 Scroll::scrollValue;

VECTOR2 Scroll::value;//�X�N���[���l

VECTOR2 Scroll::velocity(1.f, 1.f);//�X�N���[�����x

void Scroll::Update()
{
	VECTOR2 dist = value - scrollValue;

	scrollValue += dist * velocity;

}
