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

private:
	static float deltaTime;

	static float unscaledDeltaTime;

	static float lastTime;

public:
	static float timeScale;//�^�C���X�P�[��

};
