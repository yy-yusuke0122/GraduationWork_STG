#pragma once

#include <list>

class MapChip;

class MapChipManager
{
private:
	MapChipManager()
	{
	}

	~MapChipManager()
	{
	}

public:
	static void Update();

	static void Add(MapChip* _map);

	static void Erase(MapChip* _map);

private:
	static std::list<MapChip*> mapchipList;

};
