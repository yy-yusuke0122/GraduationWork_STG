#pragma once
#include "../../lib/UrLib.h"

class PlayerMover : public Component {
public:
	PlayerMover();
	~PlayerMover();
	void Start();
	void Update();
	void Move(bool _isRight);
	void Jump();
	

private:
	float speed;		// ���ړ����x���i�[���锠
	float jumpPower;	// �������x���i�[���锠
	bool randing;		// ���n���Ă��邩�ǂ������i�[���锠

private:
	void Fall();		// ��������
};