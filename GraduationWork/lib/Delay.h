#pragma once

#include "Component.h"
#include "Time.h"

template<class C, typename RET>
class Delay : public Component
{
public:
	Delay() :
		time(0.f), endTime(0.f), isUseScale(true), instance(nullptr), call(nullptr)
	{
	}

	~Delay()
	{
	}

	void Update()override
	{
		if (isUseScale)
			time += Time::DeltaTime();
		else
			time += Time::UnscaledDeltaTime();
		
		if (	call == nullptr)return;
		if (instance == nullptr)return;


		if (time > endTime)
		{
			(instance->*call)();
			time = 0.f;
		}
	}

public:
	float time;//�o�ߎ���

	float endTime;//�w��

	RET(C::* call)();//�R�[���o�b�N

	C* instance;//�C���X�^���X

	bool isUseScale;//�X�P�[���g�p�t���O

};
