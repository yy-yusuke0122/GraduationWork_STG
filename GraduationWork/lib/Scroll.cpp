#include "Time.h"
#include "Function.h"
#include "Scroll.h"

VECTOR2 Scroll::scrollValue;


bool	Scroll::isUseDeltaTime = false;

VECTOR2 Scroll::value;//スクロール値

VECTOR2 Scroll::speed(1.f, 1.f);//スクロール速さ

//Quake* Scroll::quake = nullptr;


void Scroll::Update()
{
	//if (quake != nullptr)
	//{
	//	printfDx("time : %f\n", quake->time);
	//	printfDx("cur : %f\n", quake->GetTime());
	//	printfDx("quake : %d\n", quake->IsPlay());
	//	printfDx("value : %f\n", quake->GetValue());
	//	if (quake->isPlay)
	//	{
	//		quake->Update();
	//		scrollValue = quake->GetValue();
	//	}//TODO

	//	else
	//		ScrollUpdate();//TODOやばい！！！
	//}
	//else
		ScrollUpdate();
}

//void Scroll::End()
//{
//	/*if (quake != nullptr)
//	{
//		delete quake;
//		quake = nullptr;
//	}*/
//}
//
//Quake* Scroll::GetQuake()
//{
//	if (quake == nullptr)
//		quake = new Quake();
//	return quake;
//}

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
