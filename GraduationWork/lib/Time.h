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

	/// <summary>
	/// タイムスケールをセット
	/// </summary>
	/// <param name="_scale">セットするスケール値</param>
	static void SetScale(float _scale) { unscaledDeltaTime = _scale; }

	/// <summary>
	/// タイムスケールを取得
	/// </summary>
	/// <returns>スケール値</returns>
	static float GetScale() { return timeScale; }

private:
	static float deltaTime;

	static float unscaledDeltaTime;

	static float lastTime;

	static float timeScale;

};
