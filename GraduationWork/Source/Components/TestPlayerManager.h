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

private:
	// ��ԊǗ��ϐ�
	std::string currentState;	// ���݂̏��
	VECTOR3 faceDir;			// ��̌���
	StateController* state;		// ��ԑ���
	Component* stateComp;		// ��Ԗ��̃R���|�[�l���g

	// ���������ϐ�
	JumpComponent* jumpComp;	// �W�����v�R���|�[�l���g
	PhysicalBehavior* physics;	// ���������R���|�[�l���g

	// �`��p�ϐ�
	ImageRenderer* renderer;	// �摜�`��R���|�[�l���g

private:
	void CheckLanding();
};