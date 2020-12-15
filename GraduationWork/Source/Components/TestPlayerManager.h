#pragma once
#include "../../lib/UrLib.h"

class PlayerMover;
class PlayerAttacker;
class JumpComponent;

class TestPlayerManager : public Component {
public:
	TestPlayerManager();
	~TestPlayerManager();
	void Start();
	void Update();

	/// <summary>
	/// ��������
	/// </summary>
	void FaceLeft();

	/// <summary>
	/// �E������
	/// </summary>
	void FaceRight();

	/// <summary>
	/// ��̌������擾
	/// </summary>
	/// <returns>��̌����x�N�g��</returns>
	VECTOR3 GetFaceDir() const;

	/// <summary>
	/// �X�e�[�g�R���g���[���[���擾
	/// </summary>
	/// <returns>�X�e�[�g�R���g���[���[�̃|�C���^�[</returns>
	ComponentSwitcher* GetStateController();

private:
	// ��ԊǗ��ϐ�
	VECTOR3 faceDir;			// ��̌���
	ComponentSwitcher* state;		// ��ԑ���

	// ���������ϐ�
	JumpComponent* jumpComp;	// �W�����v�R���|�[�l���g
	PhysicalBehavior* physics;	// ���������R���|�[�l���g

	// �`��p�ϐ�
	ImageRenderer* renderer;	// �摜�`��R���|�[�l���g

private:
	void CheckLanding();
};