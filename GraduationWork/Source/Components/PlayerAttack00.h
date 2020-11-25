#pragma once
#include "../../lib/UrLib.h"

class PlayerAttack00 : public Component {
public:
	PlayerAttack00();
	~PlayerAttack00();
	void Start();

	void OnCollisionEnter2D(Collider2D* _collider) override;

private:
	float power;
};