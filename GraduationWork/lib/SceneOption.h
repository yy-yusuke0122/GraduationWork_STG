#pragma once
#include "typedef.h"

class SceneOption {
public:
	SceneOption();
	~SceneOption();
	
	// �d�͊֘A
	VECTOR3 gravityDir;		// �d�͂̕���
	float gravity;			// �d�͉����x
	bool useGravity;		// �d�͌v�Z���s�����ǂ���

	// ���C�֘A
	float friction;			// ���C�W��

	// ��C��R�֘A
	float drag;				// ��C��R
};