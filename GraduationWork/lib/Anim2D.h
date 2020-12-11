#pragma once

class Anim2D {
public:
	Anim2D() :
		handle(-1), start(0), end(0), currentNum(0), speed(1.0f), loopFlag(true), time(0.0f) {}
	~Anim2D() {}

	virtual void Init() = 0;

	/// <summary>
	/// �A�j���[�V�����ԍ��̍X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �Ō�̃A�j���[�V�������ǂ���
	/// </summary>
	/// <returns>�Ō�̃A�j���[�V�����ԍ��Ȃ�true</returns>
	bool IsEndAnim() const;

	int handle;
	unsigned int start, end;
	unsigned int currentNum;
	float speed;
	bool loopFlag;

private:
	float time;
};