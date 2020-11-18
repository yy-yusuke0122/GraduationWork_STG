#pragma once

class Time
{
private:
	Time()
	{
	}

	~Time()
	{
	}

public:

	static void Init();

	static void Update();

	/// <summary>
	/// 1�t���[���ɂ����������ԁi�b�j
	/// </summary>
	/// <returns>�o�ߎ���</returns>
	static float DeltaTime() { return deltaTime; }

	/// <summary>
	/// 1�t���[���ɂ����������ԁi�b�j
	/// �X�P�[�����K������܂���
	/// </summary>
	/// <returns>�o�ߎ���</returns>
	static float UnscaledDeltaTime() { return unscaledDeltaTime; }

	/// <summary>
	/// �^�C���X�P�[�����Z�b�g
	/// </summary>
	/// <param name="_scale">�Z�b�g����X�P�[���l</param>
	static void SetScale(float _scale) { unscaledDeltaTime = _scale; }

	/// <summary>
	/// �^�C���X�P�[�����擾
	/// </summary>
	/// <returns>�X�P�[���l</returns>
	static float GetScale() { return timeScale; }

private:
	static float deltaTime;

	static float unscaledDeltaTime;

	static float lastTime;

	static float timeScale;

};
