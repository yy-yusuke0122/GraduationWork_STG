#pragma once

#include "Component.h"
#include "Time.h"

template<class C>
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

		if (time > endTime)
		{
			if (call != nullptr && instance != nullptr)
				(instance->*call)();
			time = 0.f;
		}
	}

public:
	float time;//経過時間

	float endTime;//指定

	void(C::* call)();//コールバック

	C* instance;//インスタンス

	bool isUseScale;//スケール使用フラグ

};
