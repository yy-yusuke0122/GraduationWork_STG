#pragma once

//#include "typedef.h"
#include "Quake.h"

class Object;

class Scroll
{
private:
	Scroll()
	{
	}

	~Scroll()
	{
	}

public:
//	static void Initialize();

	static void Update();

	/// <summary>
	/// ���݂̃X�N���[���l�擾
	/// </summary>
	/// <returns>�X�N���[���l</returns>
	static const VECTOR2& GetValue() { return scrollValue; }

private:
	static void ScrollUpdate();

private:
	static VECTOR2 scrollValue;

public:
	static bool isUseDeltaTime;//�X�N���[���l�ω���DeltaTime()���g�p���邩

	static VECTOR2 value;//�X�N���[���ړI�l

	static VECTOR2 speed;//�X�N���[�������i0�`1�j

	static Quake quake;

};
