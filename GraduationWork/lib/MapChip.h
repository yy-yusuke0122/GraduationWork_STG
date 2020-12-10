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

private:
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
