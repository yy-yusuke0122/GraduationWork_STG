#pragma once
#include "typedef.h"

class SceneOption {
public:
	SceneOption();
	~SceneOption();
	
	// 重力関連
	VECTOR3 gravityDir;		// 重力の方向
	float gravity;			// 重力加速度
	bool useGravity;		// 重力計算を行うかどうか

	// 摩擦関連
	float friction;			// 摩擦係数

	// 空気抵抗関連
	float drag;				// 空気抵抗
};