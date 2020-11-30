#pragma once
#include "../../lib/UrLib.h"

class PlayerAttack02 : public Component {
public:
	PlayerAttack02();
	~PlayerAttack02();
	void Start();
	void Update();

	void OnCollisionStay2D(Collider2D* _collider) override;

private:
	BoxCollider2D* box;
	float power;
	int coolTime;
};