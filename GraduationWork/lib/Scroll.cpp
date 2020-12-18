#include "Time.h"
#include "Function.h"
#include "Scroll.h"

VECTOR2 Scroll::scrollValue;


bool	Scroll::isUseDeltaTime = false;

VECTOR2 Scroll::value;//�X�N���[���l

VECTOR2 Scroll::speed(1.f, 1.f);//�X�N���[������

Quake	Scroll::quake;


void Scroll::Update()
{
	/*if (quake.IsPlay()) { quake.Update(); scrollValue = quake.GetValue(); }

	else */ScrollUpdate();//TODO��΂��I�I�I

	printfDx("scroll : x = %f, y = %f\n", scrollValue.x, scrollValue.y);

}

void Scroll::ScrollUpdate()
{
	Clamp(speed.x, 0.f, 1.f);
	Clamp(speed.y, 0.f, 1.f);

	VECTOR2 dist = value - scrollValue;

	if (isUseDeltaTime)
		scrollValue += dist * speed * Time::DeltaTime();
	else
		scrollValue += dist * speed;
}
