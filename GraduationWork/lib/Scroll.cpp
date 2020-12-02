#include "Scroll.h"

VECTOR2 Scroll::scrollValue;

VECTOR2 Scroll::value;//スクロール値

VECTOR2 Scroll::velocity(1.f, 1.f);//スクロール速度

void Scroll::Update()
{
	VECTOR2 dist = value - scrollValue;

	scrollValue += dist * velocity;

}
