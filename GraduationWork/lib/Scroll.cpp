#include "Time.h"
#include "Function.h"
#include "Scroll.h"

VECTOR2 Scroll::scrollValue;

float	Scroll::time = 0.f;

bool	Scroll::isQuake = false;

Object* Scroll::callObj = nullptr;
void	(Object::* Scroll::cCallback)() = nullptr;


bool	Scroll::isUseDeltaTime = false;

VECTOR2 Scroll::value;//�X�N���[���l

VECTOR2 Scroll::speed(1.f, 1.f);//�X�N���[������

float	Scroll::quakeTime = 1.f;//�k���̎���

VECTOR2 Scroll::quakeScale(1.f, 1.f);

void	(*Scroll::gCallback)() = nullptr;//�k���̏I�����ɌĂяo���֐��A�ďo����ɔj��

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
	value;//�k���̒��S
	speed;//����
	quakeTime;//����
	quakeScale;//�h�ꕝ
	scrollValue;//���݂̐k���l
	time;//���ݎ���

	/*
	�U����d, �ړ�������L, �ő�ʒu��Qs, ���_��V, ���Ԃ�T, ���x��S�Ƃ���
	d = Qs - v
	L = S�ET
	�ő�ɂȂ�񐔂�n, ��������a, ���݈ʒu��p�Ƃ���
	n = L / d
	L = ��i = 0(n)(d - a�Ei)
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

	//�ړI���W���Z�o

	VECTOR2 offset = quakeScale - value;
	VECTOR2 destination = value - scrollValue;
	MATRIX m = DxLib::MGetRotZ(::atan2f(destination.y, destination.x));
	VECTOR v = VTransform(VGet(scrollValue.x, scrollValue.y, 0.f), m);
	destination.x = v.x; destination.y = v.y;
	if (isQuakeUp)
		destination += quakeScale;
	else
		destination -= quakeScale;



	//�o�ߎ��Ԃ��Z�o
	float delta = Time::DeltaTime();//�o�ߎ���
	time += delta;
	if (time > quakeTime)
	{
		//�I��
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
