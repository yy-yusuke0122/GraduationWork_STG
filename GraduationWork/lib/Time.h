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
	/// 1フレームにかかった時間（秒）
	/// </summary>
	/// <returns>経過時間</returns>
	static float DeltaTime() { return deltaTime; }

	/// <summary>
	/// 1フレームにかかった時間（秒）
	/// スケールが適応されません
	/// </summary>
	/// <returns>経過時間</returns>
	static float UnscaledDeltaTime() { return unscaledDeltaTime; }

private:
	static float deltaTime;

	static float unscaledDeltaTime;

	static float lastTime;

public:
	static float timeScale;//タイムスケール

};
