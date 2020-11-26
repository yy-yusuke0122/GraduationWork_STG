#pragma once

#include "../../lib/UrLib.h"

class EnemyController;
class EnemyImageChanger;

class EnemyAttack02 :public Component
{
public:
	EnemyAttack02();

	~EnemyAttack02()
	{
	}

	void Start()override;

	void Update()override;

	void OnCollisionEnter2D(Collider2D* _collider)override;

private:
	float jumpSpeed;

	float time;

	bool isInitialize;

	int shotCount;

	float xspeed;

	EnemyController* controller;

	EnemyImageChanger* changer;

	ImageRenderer* renderer;
};
