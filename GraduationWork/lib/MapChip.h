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
	/// マップを構成
	/// </summary>
	/// <param name="_height">マップの高さ、0以下の場合無視</param>
	/// <param name="_width">マップの横、0以下の場合無視</param>
	/// <returns>true：成功、false：既に作られている</returns>
	bool Create(int _height, int _width);

	/// <summary>
	/// 破棄
	/// </summary>
	void Destroy();

	/// <summary>
	/// チップにオブジェクトを関連付ける
	/// </summary>
	/// <param name="_object">関連付けるオブジェクト</param>
	/// <returns>true：成功、false：失敗</returns>
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
