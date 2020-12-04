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
	VECTOR3 velocity;		// 加速値
	bool isLanding;			// 着地しているか

	VECTOR3 gravityDir;		// 重力の方向
	float gravity;			// 重力加速度
	bool useGravity;		// 重力計算を行うか

	float friction;			// 摩擦係数

	float drag;				// 空気抵抗

private:
};