#pragma once

class Anim2D {
public:
	Anim2D(int _handle, unsigned int _start, unsigned int _end, float _speed, bool _isLoop) :
		start(_start), end(_end), currentNum(_start), speed(_speed), isLoop(_isLoop) {}
	~Anim2D() {}

	/// <summary>
	/// 最後のアニメーションかどうか
	/// </summary>
	/// <returns>最後のアニメーション番号ならtrue</returns>
	bool IsEndAnim() const { return currentNum == end; }

	unsigned int start, end;
	unsigned int currentNum;
	float speed;
	bool isLoop;
};