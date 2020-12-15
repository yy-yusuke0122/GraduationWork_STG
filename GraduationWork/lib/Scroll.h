#pragma once

#include "typedef.h"

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
	static void Update();

	/// <summary>
	/// ���݂̃X�N���[���l�擾
	/// </summary>
	/// <returns>�X�N���[���l</returns>
	static const VECTOR2& GetValue() { return scrollValue; }

	/// <summary>
	/// �k�킹��
	/// </summary>
	static void Quake(const VECTOR2& _center) { isQuake = true; }

	/// <summary>
	/// �k���̏I�����ɌĂяo���֐����Z�b�g
	/// �ďo����ɔj��
	/// </summary>
	/// <typeparam name="C">�N���X�^</typeparam>
	/// <param name="_obj">�I�u�W�F�N�g�A�h���X</param>
	/// <param name="_call">�Ăяo���֐�</param>
	template<class C>
	static void QuakeEndCallback(C* _obj, void (C::* _call)())
	{
		callObj = _obj;
		cCallback = reinterpret_cast<void (Object::*)()> (_call);
	}

private:
	static void ScrollUpdate();

	static void QuakeUpdate();

	static void EndQuake();

private:
	static VECTOR2 scrollValue;

	static float time;

	static bool isQuake;

	static Object* callObj;
	static void (Object::*cCallback)();

public:
	static bool isUseDeltaTime;//�X�N���[���l�ω���DeltaTime()���g�p���邩

	static VECTOR2 value;//�X�N���[���ړI�l�AQuake�������_�Ƃ���

	static VECTOR2 speed;//�X�N���[�������i0�`1�j

	static float quakeTime;//�k���̎���

	static VECTOR2 quakeScale;//�k���̑傫��

	static void (*gCallback)();//�k���̏I�����ɌĂяo���֐��A�ďo����ɔj��

	static bool isQuakeUp;//�h��̕������v���X������

};
