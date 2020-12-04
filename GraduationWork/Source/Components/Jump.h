#pragma once
#include "../../lib/UrLib.h"

class PhysicalBehavior;

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
	/// �������I��������
	/// ���n�������ɌĂԊ֐�
	/// </summary>
	void Land();

	/// <summary>
	/// �W�����v������ݒ肷��
	/// </summary>
	/// <param name="_dir">�����x�N�g��</param>
	void SetJumpDir(VECTOR3 _dir);

	float jumpPower;			// �W�����v��
	unsigned int jumpCount;		// �W�����v��
	unsigned int maxJumpCount;	// �W�����v�񐔂̍ő吔

private:
	VECTOR3 jumpDir;			// �W�����v����
	PhysicalBehavior* physics;	// ���������R���|�[�l���g
};
