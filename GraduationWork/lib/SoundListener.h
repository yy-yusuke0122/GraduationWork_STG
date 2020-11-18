#pragma once

#include "dxlib/DxLib.h"

#include "Component.h"

#include "typedef.h"

class SoundListener : public Component
{
public:
	SoundListener() :
		prevPos(VGet(0.f, 0.f, 0.f))
	{
	}

	~SoundListener()
	{
	}

	void Start();

	void Update();

private:
	VECTOR3 prevPos;//前フレーム座標

};
