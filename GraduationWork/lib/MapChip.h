#pragma once

#include <vector>
#include <list>
#include "GameObject.h"

class Chip;
class ChipCollider;

class MapChip :public GameObject
{
	friend ChipCollider;

public:
	MapChip();

	~MapChip();

	void Judge();
	
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
	/// <returns>true�F�����Afalse�F���s</returns>
	bool SetChipCollider(GameObject* _object);

	/// <summary>
	/// �`�b�v���擾
	/// </summary>
	/// <param name="_h">�`�b�v�̍���</param>
	/// <param name="_w">�`�b�v�̕�</param>
	/// <returns>null�ȊO�F�`�b�v�Anull�F�͈͊O</returns>
	GameObject* GetChip(int _h, int _w);

private:
	int GetIndex(int _h, int _w)const;

	void EraseCollider(ChipCollider* _collide);

private:
	std::vector<Chip> map;

	std::list<ChipCollider*> colliderList;

	int height, width, sizeX, sizeY;

public:
	bool isLoop;//���[�v���ē����蔻�����邩

};
