#pragma once

#include "../../lib/UrLib.h"

class EnemyAttack01 :public Component
{
public:
	EnemyAttack01() :
		jumpPower(0.f), jumpSpeed(0.f), attackTime(0.3f), time(0.f), isAttacked(false)
	{
	}

	~EnemyAttack01()
	{
	}

	void Start()override;

	void Update()override;

	void Jump();

	void OnCollisionEnter2D(Collider2D* _collider)override;

public:
	float jumpPower;

	float attackTime;

private:
	float jumpSpeed;

	bool isAttacked;//çUåÇÇµÇΩÇ©

	float time;

};
