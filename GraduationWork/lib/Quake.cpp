#include "Time.h"
#include "Quake.h"

void Quake::Update()
{
	//�o�ߎ��Ԃ��Z�o
	float delta = Time::DeltaTime();//�o�ߎ���
	currentTime += delta;
	if (currentTime > time)
	{
		//�I��
		EndQuake();
		return;
	}

	/*
		�U����d, �ړ�������L, �ő�ʒu��Qs, ���_��V, ���Ԃ�T, ���x��S�Ƃ���
		d = Qs - v
		L = S�ET
		�ő�ɂȂ�񐔂�n, ��������a, ���݈ʒu��p�Ƃ���
		n = L / d
		an = d
		a = d / n
		a = (Qs - v) / (S�ET / (Qs - v))
		a = (Qs - v) * ((Qs - v) / S�ET)
		a = (Qs - v)^2 / S�ET
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
		a.x = d2.x / (speed.x * time);//����

	if (speed.y != 0.f)
		a.y = d2.y / (speed.y * time);

	VECTOR2 n;//���ݐU����
	if (!dxzero)
		n.x = currentTime * speed.x / scale.x;
	if (!dyzero)
		n.y = currentTime * speed.y / scale.y;

	VECTOR2 ni(static_cast<float>(static_cast<int>(n.x)),
		static_cast<float>(static_cast<int>(n.y)));//���ݐU�����A�[���؎̂�

	VECTOR2 atten(ni.x * a.x, ni.y * a.y);//����

	VECTOR2 s = scale - atten;//���ݐU��

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
