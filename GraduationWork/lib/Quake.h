#pragma once

#include "typedef.h"

class Object;

class Quake
{
public:
	Quake() :
		currentTime(0.f), callObj(nullptr), cCallback(nullptr),
		time(1.f), scale(1.f, 1.f), gCallback(nullptr), speed(1.f, 1.f), isPlay(false)
	{
	}

	~Quake()
	{
	}

	void Update();

	/// <summary>
	/// �k�킹��
	/// </summary>
	void Play()
	{
		isPlay = true;
	}

	/// <summary>
	/// �k���̏I�����ɌĂяo���֐����Z�b�g
	/// �ďo����ɔj��
	/// </summary>
	/// <typeparam name="C">�N���X�^</typeparam>
	/// <param name="_obj">�I�u�W�F�N�g�A�h���X</param>
	/// <param name="_call">�Ăяo���֐�</param>
	template<class C>
	void QuakeEndCallback(C* _obj, void (C::* _call)())
	{
		callObj = _obj;
		cCallback = reinterpret_cast<void (Object::*)()> (_call);
	}

	/// <summary>
	/// Play����̌o�ߎ��Ԃ��擾
	/// </summary>
	/// <returns>�o�ߎ���</returns>
	float GetTime()const { return currentTime; }

	/// <summary>
	/// Quake�����擾
	/// </summary>
	/// <returns>true�FQuake���Afalse�FPlay�҂�</returns>
	bool IsPlay()const { return isPlay; }

	/// <summary>
	/// �R�[���o�b�N����I�u�W�F�N�g���擾
	/// </summary>
	/// <returns>�Ăяo���I�u�W�F�N�g</returns>
	Object* GetObj()const { return callObj; }

	/// <summary>
	/// �R�[���o�b�N���郁�\�b�h���擾
	/// </summary>
	/// <returns>�Ăяo�����\�b�h</returns>
	auto GetCallBack() { return cCallback; };

	/// <summary>
	/// Quake�̒l���擾
	/// </summary>
	/// <returns>Quake�l</returns>
	const VECTOR2& GetValue()const { return value; }

private:
	void EndQuake();

private:
	float currentTime;

	Object* callObj;
	void (Object::* cCallback)();

	VECTOR2 value;

public:
	VECTOR2 center;//���S

	float time;//�k���̎���

	VECTOR2 scale;//�k���̑傫��

	VECTOR2 speed;//�X�N���[������

	void (*gCallback)();//�k���̏I�����ɌĂяo���֐��A�ďo����ɔj��

private:
	bool isPlay;
};
