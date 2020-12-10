#include "Time.h"
#include "dxlib/DxLib.h"

float Time::deltaTime = 0.f;

float Time::unscaledDeltaTime = 0.f;

float Time::lastTime = 0.f;

float Time::timeScale = 1.f;

namespace
{
	float GetTime() { return static_cast<float>(GetNowCount()) / 1000.f; }
}

void Time::Init()
{
	lastTime = GetTime();
}

void Time::Update()
{
	float time = GetTime();

	unscaledDeltaTime = time - lastTime;

	deltaTime = unscaledDeltaTime * timeScale;

	if (deltaTime == 0.f)
	{
		int a = 0;
	}

	lastTime = time;
}
