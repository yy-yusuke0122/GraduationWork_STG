#pragma once
#include "../../lib/UrLib.h"

class JumpComponent : public Component {
public:
	JumpComponent();
	~JumpComponent();
	void Start() override;
	void Update() override;

	/// <summary>
	/// �W�����v����
	/// �W�����v�񐔂�����𒴂���ꍇ��������
	/// </summary>
	void Jump();

	/// <summary>
	/// �W�����v������ݒ肷��
	/// </summary>
	/// <param name="_dir">�����x�N�g��</param>
	void SetJumpDir(VECTOR2 _dir);

	float jumpPower;			// �W�����v��
	unsigned int jumpCount;		// �W�����v��
	unsigned int maxJumpCount;	// �W�����v�񐔂̍ő吔
	VECTOR2 localGravity;		// �d�̓x�N�g��
private:
	VECTOR2 jumpDir;			// �W�����v����
	VECTOR2 fallVec;			// �����x�N�g��
	bool isLanding;				// ���n���Ă��邩
};
