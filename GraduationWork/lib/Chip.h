#pragma once

#include <unordered_map>
#include <string>
#include <typeinfo>
#include "GameObject.h"

class Component;
class MapChip;

class Chip :public GameObject
{
	friend MapChip;

public:
	Chip() :
		map(nullptr), h(0), w(0), type(0)
	{
	}

	~Chip()
	{
	}

	/// <summary>
	/// �}�b�v��ł̐��������̈ʒu
	/// </summary>
	/// <returns>���������ʒu</returns>
	int GetH()const { return h; }

	/// <summary>
	/// �}�b�v��ł̐��������̈ʒu
	/// </summary>
	/// <returns>���������ʒu</returns>
	int GetW()const { return w; }

	/// <summary>
	/// �}�b�v���擾
	/// </summary>
	/// <returns>�}�b�v</returns>
	MapChip* GetMap()const { return map; }

private:
	MapChip* map;

	int h, w;

public:
	int type;//���[�U�[�w��l

};
