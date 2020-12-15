#include "Time.h"
#include "Function.h"
#include "Scroll.h"

VECTOR2 Scroll::scrollValue;

float	Scroll::time = 0.f;

bool	Scroll::isQuake = false;

Object* Scroll::callObj = nullptr;
void	(Object::* Scroll::cCallback)() = nullptr;


bool	Scroll::isUseDeltaTime = false;

VECTOR2 Scroll::value;//スクロール値

VECTOR2 Scroll::speed(1.f, 1.f);//スクロール速さ

float	Scroll::quakeTime = 1.f;//震えの時間

VECTOR2 Scroll::quakeScale(1.f, 1.f);

void	(*Scroll::gCallback)() = nullptr;//震えの終了時に呼び出す関数、呼出し後に破棄

bool Scroll::isQuakeUp = true;


void Scroll::Update()
{
	Clamp(speed.x, 0.f, 1.f);
	Clamp(speed.y, 0.f, 1.f);

	if (isQuake)ScrollUpdate();

	else		QuakeUpdate();

}

void Scroll::ScrollUpdate()
{
	VECTOR2 dist = value - scrollValue;

	if (isUseDeltaTime)
		scrollValue += dist * speed * Time::DeltaTime();
	else
		scrollValue += dist * speed;
}

void Scroll::QuakeUpdate()
{
	value;//震えの中心
	speed;//速さ
	quakeTime;//時間
	quakeScale;//揺れ幅
	scrollValue;//現在の震え値
	time;//現在時間

	/*
	振幅をd, 移動距離をL, 最大位置をQs, 原点をV, 時間をT, 速度をSとする
	d = Qs - v
	L = S・T
	最大になる回数をn, 減衰率をa, 現在位置をpとする
	n = L / d
	L = Σi = 0(n)(d - a・i)
	an = d
	L = d(d - a)(d - 2a)(d - 3a)...(d - (n - 1)a)
	L = an(an - a)(an - 2a)(an - 3a)...(an - (n - 1)a)
	L = n(n - 1)(n - 2)(n - 3)...1
	n = L / ((n - 1)(n - 2)(n - 3)...1)
	a = d / n
	a = (Qs - v) / (L / ((n - 1)(n - 2)(n - 3)...1))
	*/

	//VECTOR2 d = quakeScale - value;
	//VECTOR2 L = speed * quakeTime;

	//VECTOR2 n = L / d;

	//VECTOR2 

	//目的座標を算出

	VECTOR2 offset = quakeScale - value;
	VECTOR2 destination = value - scrollValue;
	MATRIX m = DxLib::MGetRotZ(::atan2f(destination.y, destination.x));
	VECTOR v = VTransform(VGet(scrollValue.x, scrollValue.y, 0.f), m);
	destination.x = v.x; destination.y = v.y;
	if (isQuakeUp)
		destination += quakeScale;
	else
		destination -= quakeScale;



	//経過時間を算出
	float delta = Time::DeltaTime();//経過時間
	time += delta;
	if (time > quakeTime)
	{
		//終了
		scrollValue = value;
		EndQuake();
		return;
	}



}

void Scroll::EndQuake()
{
	if (cCallback != nullptr && callObj != nullptr)
		(callObj->*cCallback)();

	if (gCallback != nullptr)
		gCallback();

	callObj = nullptr;
	cCallback = nullptr;
	gCallback = nullptr;

	quakeTime = 0.f;

	isQuake = false;
}
