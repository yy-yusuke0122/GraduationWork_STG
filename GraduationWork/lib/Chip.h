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
	/// マップ上での垂直方向の位置
	/// </summary>
	/// <returns>垂直方向位置</returns>
	int GetH()const { return h; }

	/// <summary>
	/// マップ上での水平方向の位置
	/// </summary>
	/// <returns>水平方向位置</returns>
	int GetW()const { return w; }

	/// <summary>
	/// マップを取得
	/// </summary>
	/// <returns>マップ</returns>
	MapChip* GetMap()const { return map; }

private:
	MapChip* map;

	int h, w;

public:
	int type;//ユーザー指定値

};
