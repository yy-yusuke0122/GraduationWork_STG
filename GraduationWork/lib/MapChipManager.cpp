#include "MapChip.h"
#include "MapChipManager.h"

std::list<MapChip*> MapChipManager::mapchipList;

void MapChipManager::Update()
{
	for (MapChip* p : mapchipList)
		p->Judge();
}

void MapChipManager::Add(MapChip* _map)
{
	mapchipList.emplace_back(_map);
}

void MapChipManager::Erase(MapChip* _map)
{
	for (std::list<MapChip*>::iterator it = mapchipList.begin(), end = mapchipList.end(); it != end; ++it)
		if ((*it) == _map)
		{
			mapchipList.erase(it);
			break;
		}
}
