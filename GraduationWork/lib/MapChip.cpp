#include "UrLib.h"

void MapChip::Update()
{

}

bool MapChip::Create(int _height, int _width)
{
	if (map.size() == 0ull)return false;

	if (_height > 0)
		height = _height;
	if (_width > 0)
		width = _width;

	SceneManager::GetCurrentScene()->Instantiate(_height * _width, map);

	return true;
}

void MapChip::Destroy()
{
	map.clear();
}

bool MapChip::SetChipObject(GameObject* _object)
{
	if (_object != nullptr)
	{
//		_object->
		return true;
	}
	return false;
}

int MapChip::GetIndex(int _h, int _w) const
{
	if (_h < height && _w < width)
		return _h * height + _w;
	return -1;
}
