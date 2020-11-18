#pragma once
#include "Collider.h"
#include "typedef.h"
#include <list>

class Collider2D : public Collider {
public:
	Collider2D();
	virtual ~Collider2D();

	virtual bool IsCollide(Collider2D* _collider) = 0;

	/// <summary>
	/// �Փˎ��ɌĂ΂��֐���S�Ď��s����
	/// </summary>
	/// <param name="_collider">�Փ˂����I�u�W�F�N�g�̃R���C�_�[</param>
	void ExecuteAllCollisionEnter(Collider2D* _collider);

	/// <summary>
	/// �Փ˒��ɌĂ΂��֐���S�Ď��s����
	/// </summary>
	/// <param name="_collider">�Փ˒��̃I�u�W�F�N�g�̃R���C�_�[</param>
	void ExecuteAllCollisionStay(Collider2D* _collider);

	/// <summary>
	/// �ՓˏI�����ɌĂ΂��֐���S�Ď��s����
	/// </summary>
	/// <param name="_collider">�ՓˏI�������I�u�W�F�N�g�̃R���C�_�[</param>
	void ExecuteAllCollisionExit(Collider2D* _collider);

	/// <summary>
	/// ���[���h���W��̃R���C�_�[���W�̎擾
	/// </summary>
	/// <returns>���[���h���W��̃R���C�_�[���W</returns>
	virtual Point2D GetWorldPosition() = 0;
};