#pragma once
#include "../../lib/UrLib.h"

class PlayerAttack01 : public Component {
public:
	PlayerAttack01();
	~PlayerAttack01();
	void Start();
	void Update();

	void OnCollisionEnter2D(Collider2D* _collider) override;

private:
	BoxCollider2D* box;
	float power;
};