#pragma once
#include "lib/UrLib.h"

class TestCollisionComponent : public Component {
public:
	void Start();
	void Update();
	void OnCollisionEnter2D(Collider2D* _collider) override;
	void OnCollisionStay2D(Collider2D* _collider) override;
private:
};