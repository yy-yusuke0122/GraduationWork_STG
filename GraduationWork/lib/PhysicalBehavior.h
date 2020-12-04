#pragma once
#include "UrLib.h"

class SceneOption;

class PhysicalBehavior : public Component {
public:
	PhysicalBehavior();
	~PhysicalBehavior();
	void Start() override;
	void PostUpdate() override;

public:
	VECTOR3 velocity;		// �����l
	bool isLanding;			// ���n���Ă��邩

	VECTOR3 gravityDir;		// �d�͂̕���
	float gravity;			// �d�͉����x
	bool useGravity;		// �d�͌v�Z���s����

	float friction;			// ���C�W��

	float drag;				// ��C��R

private:
};