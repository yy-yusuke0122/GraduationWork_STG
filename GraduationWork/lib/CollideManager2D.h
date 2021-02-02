#pragma once
#include <list>

template<class T>
class CLiner4TreeManager;
template<class T>
class OBJECT_FOR_TREE;

class Collider;
class Collider2D;

class CollideManager2D {
public:
	CollideManager2D();
	~CollideManager2D();

	/// <summary>
	/// ������
	/// </summary>
	void Init(unsigned int Level = 8, float left = -1000.0f, float top = -1000.0f, float right = 1000.0f, float bottom = 1000.0f);

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
	struct COL_PAIR {
		Collider2D* col1;
		Collider2D* col2;
		COL_PAIR(Collider2D* _col1, Collider2D* _col2) : col1(_col1), col2(_col2) {}
		~COL_PAIR() {}
	};
	std::list<COL_PAIR> currentCollideList;
	CLiner4TreeManager<Collider2D>* LTree;
	std::list<OBJECT_FOR_TREE<Collider2D>*> pOFTAry;
private:
	void CheckCollideEnter(Collider2D* _col1, Collider2D* _col2);
	bool CheckCollideStay(Collider2D* _col1, Collider2D* _col2);

	/// <summary>
	/// ���ɏՓ˂��Ă��邩���m�F����
	/// ���ɏՓ˂��Ă����ꍇ�A�����̃C�e���[�^�ɑ�������
	/// </summary>
	/// <param name="_colInfo">�m�F����Փ˃��X�g������COL_INFO</param>
	/// <param name="_col2">���ɏՓ˂��Ă��邩�m�F����R���C�_�[</param>
	/// <param name="_it">���ɏՓ˂��Ă���R���C�_�[���w���C�e���[�^</param>
	/// <returns>���ɏՓ˂��Ă����true</returns>
	//bool IsCollided(COL_INFO* _colInfo, Collider2D* _col, std::list<Collider2D*>::iterator& _it);
	bool IsCollided(Collider2D* _col1, Collider2D* _col2);
};