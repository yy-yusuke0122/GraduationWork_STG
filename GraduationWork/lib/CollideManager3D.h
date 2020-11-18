#pragma once
#include <list>

class Collider;
class Collider3D;

class CollideManager3D {
public:
	CollideManager3D();
	~CollideManager3D();

	/// <summary>
	/// �����蔻����m�F
	/// </summary>
	void Update();

	/// <summary>
	/// Collider2D���Ǘ����ɒǉ�����
	/// </summary>
	/// <param name="_col">�ǉ�������Collider</param>
	/// <returns>true:����, false:���ɓo�^����Ă���</returns>
	bool PushCollider(Collider3D* _col);

	/// <summary>
	/// �R���C�_�[���Ǘ�������O��
	/// �R���C�_�[�폜���Ɏ����ŌĂ΂��̂ŁA���ڌĂ΂Ȃ�����
	/// </summary>
	void RemoveCollider(Collider3D* _col);

private:
	struct COL_INFO {
		Collider3D* col;
		std::list<Collider3D*> currentCollideList;
		COL_INFO(Collider3D* _col) : col(_col) {}
		~COL_INFO() {}
	};
	std::list<COL_INFO*> colliderList;
private:
	/// <summary>
	/// ���݂����Փ˂��Ă��邩���m�F���A
	/// �Փˎ��͑Ή������֐����Ă�
	/// </summary>
	void CheckCollider(COL_INFO* _col1, COL_INFO* _col2);

	/// <summary>
	/// ���ɏՓ˂��Ă��邩���m�F����
	/// ���ɏՓ˂��Ă����ꍇ�A�����̃C�e���[�^�ɑ�������
	/// </summary>
	/// <param name="_colInfo">�m�F����Փ˃��X�g������COL_INFO</param>
	/// <param name="_col2">���ɏՓ˂��Ă��邩�m�F����R���C�_�[</param>
	/// <param name="_it">���ɏՓ˂��Ă���R���C�_�[���w���C�e���[�^</param>
	/// <returns>���ɏՓ˂��Ă����true</returns>
	bool IsCollided(COL_INFO* _colInfo, Collider3D* _col, std::list<Collider3D*>::iterator& _it);
};