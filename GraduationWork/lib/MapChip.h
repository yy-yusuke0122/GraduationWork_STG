#pragma once

#include <vector>
#include <list>

class Chip;
class ChipCollider;

class MapChip
{
public:
	MapChip() :
		height(1), width(1)
	{
	}

	~MapChip()
	{
		Destroy();
	}

	void Update();
	
	/// <summary>
	/// �}�b�v���\��
	/// </summary>
	/// <param name="_height">�}�b�v�̍����A0�ȉ��̏ꍇ����</param>
	/// <param name="_width">�}�b�v�̉��A0�ȉ��̏ꍇ����</param>
	/// <returns>true�F�����Afalse�F���ɍ���Ă���</returns>
	bool Create(int _height, int _width);

	/// <summary>
	/// �j��
	/// </summary>
	void Destroy();

	/// <summary>
	/// �`�b�v�ɃI�u�W�F�N�g���֘A�t����
	/// </summary>
	/// <param name="_object">�֘A�t����I�u�W�F�N�g</param>
	/// <returns>true�F�����Afalse�F���s</returns>
	bool SetChipObject(GameObject* _object);

	void CollisionX() {}

	void CollisionY() {}

private:
	int GetIndex(int _h, int _w)const;

private:
	std::vector<Chip> map;

	std::list<ChipCollider*> colliderList;

	int height, width;

};
