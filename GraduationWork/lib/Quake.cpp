#include "Time.h"
#include "Quake.h"

void Quake::Update()
{
	//経過時間を算出
	float delta = Time::DeltaTime();//経過時間
	currentTime += delta;
	if (currentTime > time)
	{
		//終了
		EndQuake();
		return;
	}

	/*
		振幅をd, 移動距離をL, 最大位置をQs, 原点をV, 時間をT, 速度をSとする
		d = Qs - v
		L = S・T
		最大になる回数をn, 減衰率をa, 現在位置をpとする
		n = L / d
		an = d
		a = d / n
		a = (Qs - v) / (S・T / (Qs - v))
		a = (Qs - v) * ((Qs - v) / S・T)
		a = (Qs - v)^2 / S・T
	*/

	bool dxzero = scale.x == 0.f;
	bool dyzero = scale.y == 0.f;

	if (dxzero && dyzero)
	{
		EndQuake();
		return;
	}

	if (dxzero)speed.x = 0.f;
	if (dyzero)speed.y = 0.f;

	if (speed == VECTOR2::zero())
	{
		EndQuake();
		return;
	}

	VECTOR2 d2 = scale * scale;

	VECTOR2 a;
	if (speed.x != 0.f)
		a.x = d2.x / (speed.x * time);//減衰

	if (speed.y != 0.f)
		a.y = d2.y / (speed.y * time);

	VECTOR2 n;//現在振幅数
	if (!dxzero)
		n.x = currentTime * speed.x / scale.x;
	if (!dyzero)
		n.y = currentTime * speed.y / scale.y;

	VECTOR2 ni(static_cast<float>(static_cast<int>(n.x)),
		static_cast<float>(static_cast<int>(n.y)));//現在振幅数、端数切捨て

	VECTOR2 atten(ni.x * a.x, ni.y * a.y);//減衰

	VECTOR2 s = scale - atten;//現在振幅

	if (static_cast<int>(n.x) % 2)
		value.x = (n.x - ni.x) * s.x;
	else
		value.x = 1.f - (n.x - ni.x) * s.x;

	if (static_cast<int>(n.y) % 2)
		value.y = (n.y - ni.y) * s.y;
	else
		value.y = 1.f - (n.y - ni.y) * s.y;

	value += center;

	printfDx("time : %f\n", time);
}

void Quake::EndQuake()
{
	value = center;

	if (cCallback != nullptr && callObj != nullptr)
		(callObj->*cCallback)();

	if (gCallback != nullptr)
		gCallback();

	callObj = nullptr;
	cCallback = nullptr;
	gCallback = nullptr;

	time = 0.f;
	currentTime = 0.f;

	isQuake = false;
}
