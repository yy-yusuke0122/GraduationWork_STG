#pragma once
#include <list>

class Collider;
class Collider2D;

class CollideManager2D {
public:
	CollideManager2D();
	~CollideManager2D();

	/// <summary>
	/// �����蔻����m�F
	/// </summary>
	void Update();

	/// <summary>
	/// Collider2D���Ǘ����ɒǉ�����
	/// </summary>
	/// <param name="_col">�ǉ�������Collider</param>
	/// <returns>true:����, false:���ɓo�^����Ă���</returns>
	bool PushCollider(Collider2D* _col);

	/// <summary>
	/// �R���C�_�[���Ǘ�������O��
	/// �R���C�_�[�폜���Ɏ����ŌĂ΂��̂ŁA���ڌĂ΂Ȃ�����
	/// </summary>
	void RemoveCollider(Collider2D* _col);

private:
	struct COL_INFO {
		Collider2D* col;
		std::list<Collider2D*> currentCollideList;
		COL_INFO(Collider2D* _col) : col(_col) {}
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
	bool IsCollided(COL_INFO* _colInfo, Collider2D* _col, std::list<Collider2D*>::iterator& _it);
};