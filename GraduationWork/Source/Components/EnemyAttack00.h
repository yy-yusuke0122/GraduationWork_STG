#pragma once

#include "../../lib/UrLib.h"

class EnemyController;

class EnemyAttack00 :public Component
{
public:
	EnemyAttack00();

	~EnemyAttack00()
	{
	}

	void Start()override;

	void Update()override;

private:
	void Jump();

	void OnCollisionStay2D(Collider2D* _collider)override;

private:	
	float attackTime;

	float jumpSpeed;

	bool isAttacked;//çUåÇÇµÇΩÇ©

	bool isInitialize;

	float time;

	float stageY;

	EnemyController* controller;
	CircleCollider2D* circle;

};
