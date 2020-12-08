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
	/// マップを構成
	/// </summary>
	/// <param name="_height">マップの高さ、0以下の場合無視</param>
	/// <param name="_width">マップの横、0以下の場合無視</param>
	/// <param name="_sizeX">チップ横サイズ</param>
	/// <param name="_sizeY">チップ縦サイズ</param>
	/// <returns>true：成功、false：既に作られている</returns>
	bool Create(int _height, int _width, int _sizeX, int _sizeY);

	/// <summary>
	/// 破棄
	/// </summary>
	void Clear();

	/// <summary>
	/// オブジェクトに当たり判定を付ける
	/// </summary>
	/// <param name="_object">当たり判定を付けるオブジェクト</param>
	/// <returns>true：成功、false：失敗</returns>
	bool SetChipCollider(GameObject* _object);

	/// <summary>
	/// チップを取得
	/// </summary>
	/// <param name="_h">チップの高さ</param>
	/// <param name="_w">チップの幅</param>
	/// <returns>null以外：チップ、null：範囲外</returns>
	GameObject* GetChip(int _h, int _w);

private:
	int GetIndex(int _h, int _w)const;

	void EraseCollider(ChipCollider* _collide);

private:
	std::vector<Chip> map;

	std::list<ChipCollider*> colliderList;

	int height, width, sizeX, sizeY;

public:
	bool isLoop;//ループして当たり判定を取るか

};
