#pragma once

#include <vector>
#include <list>
#include "GameObject.h"

class Chip;
class ChipCollider;

class MapChip :public GameObject
{
	friend ChipCollider;

private:
	struct Searcher
	{
		bool Search(int _type) { return (this->*search)(_type); };

		void SetG(bool (*_f)(int)) { g_search = _f; search = &Searcher::SearchG; }
		void SetO(GameObject* _obj, bool(GameObject::* _f)(int))
			{ obj = _obj; o_search = _f; search = &Searcher::SearchM; }
		void SetC(Component* _comp, bool (Component::* _f)(int))
			{ comp = _comp; c_search = _f; search = &Searcher::SearchC; }

	private:
		bool (Searcher::* search)(int);
		
		bool SearchG(int _type) { return g_search(_type); }
		bool SearchM(int _type) { return (obj->*o_search)(_type); }
		bool SearchC(int _type) { return (comp->*c_search)(_type); }
		bool (GameObject::* o_search)(int);
		bool (Component::* c_search)(int);
		bool (*g_search)(int);
		GameObject* obj;
		Component* comp;
	};

public:
	MapChip();

	~MapChip();

	void ChipUpdate();

	void PostChipUpdate();

	void CheckCollide();
	
	/// <summary>
	/// �}�b�v���\��
	/// </summary>
	/// <param name="_height">�}�b�v�̍����A0�ȉ��̏ꍇ����</param>
	/// <param name="_width">�}�b�v�̉��A0�ȉ��̏ꍇ����</param>
	/// <param name="_sizeX">�`�b�v���T�C�Y</param>
	/// <param name="_sizeY">�`�b�v�c�T�C�Y</param>
	/// <returns>true�F�����Afalse�F���ɍ���Ă���</returns>
	bool Create(int _height, int _width, int _sizeX, int _sizeY);

	/// <summary>
	/// �j��
	/// </summary>
	void Clear();
	
	/// <summary>
	/// �I�u�W�F�N�g�ɓ����蔻���t����
	/// </summary>
	/// <param name="_object">�����蔻���t����I�u�W�F�N�g</param>
	/// <param name="_xsize">�����A�}�C�i�X�l�Ń`�b�v�̃T�C�Y�����蓖�Ă�</param>
	/// <param name="_ysize">�c���A�}�C�i�X�l�Ń`�b�v�̃T�C�Y�����蓖�Ă�</param>
	/// <returns>true�F�����Afalse�F���s</returns>
	bool SetChipCollider(GameObject* _object, int _xsize = -1, int _ysize = -1);

	/// <summary>
	/// �����蔻��̃T�C�Y���Z�b�g
	/// </summary>
	/// <param name="_object">�Z�b�g����I�u�W�F�N�g</param>
	/// <param name="_xsize">�Z�b�g���鉡���A�}�C�i�X�Ń`�b�v�T�C�Y�Anull�Ŗ���</param>
	/// <param name="_ysize">�Z�b�g����c���A�}�C�i�X�Ń`�b�v�T�C�Y�Anull�Ŗ���</param>
	/// <returns>true�F�����Afalse�F�I�u�W�F�N�g�����݂��Ȃ�</returns>
	bool SetColliderSize(GameObject* _object, int* _xsize, int* _ysize);

	/// <summary>
	/// �����蔻��̃T�C�Y���擾
	/// </summary>
	/// <param name="_object">�擾����I�u�W�F�N�g</param>
	/// <param name="_xsize">�����i�[�Anull�Ŗ���</param>
	/// <param name="_ysize">�c���i�[�Anull�Ŗ���</param>
	/// <returns>true�F�����Afalse�F�I�u�W�F�N�g�����݂��Ȃ�</returns>
	bool GetColliderSize(GameObject* _object, int* _xsize, int* _ysize);

	/// <summary>
	/// �`�b�v���擾
	/// </summary>
	/// <param name="_h">�`�b�v�̍���</param>
	/// <param name="_w">�`�b�v�̕�</param>
	/// <returns>null�ȊO�F�`�b�v�Anull�F�͈͊O</returns>
	Chip* GetChip(int _h, int _w);

	/// <summary>
	/// �}�b�v�̍����擾
	/// </summary>
	/// <returns>����</returns>
	int GetHeight()const { return height; }

	/// <summary>
	/// �}�b�v�̕��擾
	/// </summary>
	/// <returns>��</returns>
	int GetWidth()const { return width; }

	/// <summary>
	/// �`�b�v�̍����擾
	/// </summary>
	/// <returns>����</returns>
	int GetSizeY()const { return sizeY; }

	/// <summary>
	/// �`�b�v�̕��擾
	/// </summary>
	/// <returns>��</returns>
	int GetSizeX()const { return sizeX; }

	/// <summary>
	/// �o�H�T��
	/// </summary>
	/// <param name="_obj">�o�H�T�����s���I�u�W�F�N�g</param>
	/// <param name="_h">�J�n��Y�ʒu</param>
	/// <param name="_w">�J�n��X�ʒu</param>
	/// <param name="_desH">�ړI�n��Y�ʒu</param>
	/// <param name="_desW">�ړI�n��X�ʒu</param>
	/// <param name="_callObj">�R�[���o�b�N����I�u�W�F�N�g</param>
	/// <param name="_isContinue">�`�b�v�̎�ނ��ʂ蔲�����邩����A�߂�l�Etrue�F�ʂ��Afalse�F�ʂ�Ȃ�</param>
	/// <param name="_outH">�Œ[���[�g�̎��ɐi��Y�ʒu</param>
	/// <param name="_outW">�Œ[���[�g�̎��ɐi��X�ʒu</param>
	/// <returns>true�F�����Afalse�F���s�i�������s���A���ǂ蒅���Ȃ��A�Œ[���[�g�͊i�[���܂��j</returns>
	bool FindRoute(int _h, int _w, int _desH, int _desW, GameObject* _callObj, bool (GameObject::* _isContinue)(int), int& _outH, int& _outW);

	/// <summary>
	/// �o�H�T��
	/// </summary>
	/// <param name="_h">�J�n��Y�ʒu</param>
	/// <param name="_w">�J�n��X�ʒu</param>
	/// <param name="_desH">�ړI�n��Y�ʒu</param>
	/// <param name="_desW">�ړI�n��X�ʒu</param>
	/// <param name="_callComp">�R�[���o�b�N����R���|�[�l���g</param>
	/// <param name="_isContinue">�`�b�v�̎�ނ��ʂ蔲�����邩����A�߂�l�Etrue�F�ʂ��Afalse�F�ʂ�Ȃ�</param>
	/// <param name="_outH">�Œ[���[�g�̎��ɐi��Y�ʒu</param>
	/// <param name="_outW">�Œ[���[�g�̎��ɐi��X�ʒu</param>
	/// <returns>true�F�����Afalse�F���s�i�������s���A���ǂ蒅���Ȃ��A�Œ[���[�g�͊i�[���܂��j</returns>
	bool FindRoute(int _h, int _w, int _desH, int _desW, Component* _callComp, bool (Component::* _isContinue)(int), int& _outH, int& _outW);

	/// <summary>
	/// �o�H�T��
	/// </summary>
	/// <param name="_h">�J�n��Y�ʒu</param>
	/// <param name="_w">�J�n��X�ʒu</param>
	/// <param name="_desH">�ړI�n��Y�ʒu</param>
	/// <param name="_desW">�ړI�n��X�ʒu</param>
	/// <param name="_isContinue">�`�b�v�̎�ނ��ʂ蔲�����邩����A�߂�l�Etrue�F�ʂ��Afalse�F�ʂ�Ȃ�</param>
	/// <param name="_outH">�Œ[���[�g�̎��ɐi��Y�ʒu�A���ǂ蒅���Ȃ��ꍇ�ŋߓ_���i�[</param>
	/// <param name="_outW">�Œ[���[�g�̎��ɐi��X�ʒu�A���ǂ蒅���Ȃ��ꍇ�ŋߓ_���i�[</param>
	/// <returns>true�F�����Afalse�F���s�i�������s����-1���i�[���܂��A���ǂ蒅���Ȃ����ŋߓ_���i�[���܂��j</returns>
	bool FindRoute(int _h, int _w, int _desH, int _desW, bool (*_isContinue)(int), int& _outH, int& _outW);

private:
	bool RouteSearch(int _h, int _w, int _desH, int _desW, Searcher&_searcher, int& _outH, int& _outW);

	int GetIndex(int _h, int _w)const;

	void EraseCollider(ChipCollider* _collide);

	void CheckOverlap(Chip* _chips[4]);

private:
	std::vector<Chip> map;

	std::list<ChipCollider*> colliderList;

	int height, width, sizeX, sizeY;

public:
	bool isLoopX, isLoopY;//���[�v���ē����蔻�����邩

};
