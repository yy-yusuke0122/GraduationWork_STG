#include "ChipCollider.h"
#include "Chip.h"
#include "MapChipManager.h"
#include "UrLib.h"

MapChip::MapChip() :
	height(1), width(1), sizeX(1), sizeY(1), isLoop(false)
{
	MapChipManager::Add(this);
}

MapChip::~MapChip()
{
	Destroy();
	for (ChipCollider* p : colliderList)
	{
		p->map = nullptr;
		p->gameObject->RemoveComponent<ChipCollider>();
	}
	MapChipManager::Erase(this);
}

void MapChip::Judge()
{
	int hsizeX = sizeX / 2;
	int hsizeY = sizeY / 2;

	for (std::list<ChipCollider*>::iterator it = colliderList.begin(), end = colliderList.end(); it != end; ++it)
	{		
		GameObject* obj = (*it)->gameObject;
		Transform* trans = (*it)->transform;

		int x = static_cast<int>(trans->position.x);
		int y = static_cast<int>(trans->position.y);

		int  left = (x - hsizeX) / sizeX;
		int	   up = (y - hsizeY) / sizeY;
		int right = left + 1;
		int  down =	  up + 1;

		if (isLoop)
		{
			left  %= width;
			up	  %= height;
			right %= width;
			down  %= height;
		}
		else
		{
			auto mincheck = [](int& _i, float& _pos, int _hsize)
			{
				if (_i < 0)
				{
					_i = 0;
					_pos = static_cast<float>(_hsize);
				}
			};

			auto maxcheck = [](int& _i, int _max, float& _pos, int _size, int _hsize)
			{
				if (_i >= _max)
				{
					_i = _max - 1;
					_pos = static_cast<float>(_max * _size - _hsize);
				}
			};

			mincheck(left, trans->position.x, hsizeX);
			mincheck(  up, trans->position.y, hsizeY);
			maxcheck(right,  width, trans->position.x, sizeX, hsizeX);
			maxcheck( down, height, trans->position.y, sizeY, hsizeY);
		}

		Chip* chips[4]{};

		//当たっているチップを格納
		chips[0] = &map[GetIndex(  up,  left)];
		chips[1] = &map[GetIndex(  up, right)];
		chips[2] = &map[GetIndex(down,  left)];
		chips[3] = &map[GetIndex(down, right)];

		//Stay呼出し
		for (Chip*& p : chips)
		{
			//当たっていた場合は即終了
			if ((*it)->CheckCollide(p))
				p = nullptr;
		}

		//Exit呼出し
		(*it)->ClearChip();//当たっていないチップを消す

		//Enter呼出し
		for (Chip* p : chips)
		{
			//初めて当たった場合は追加
			if (p != nullptr)
				(*it)->AddChip(p);
		}
	}
}

bool MapChip::Create(int _height, int _width, int _sizeX, int _sizeY)
{
	if (map.size() == 0ull)return false;

	if (_height > 0)
		height = _height;
	if (_width > 0)
		width = _width;
	if (_sizeX > 0)
		sizeX = _sizeX;
	if (_sizeY > 0)
		sizeY = _sizeY;

	SceneManager::GetCurrentScene()->Instantiate(_height * _width, map);

	return true;
}

void MapChip::Clear()
{
	map.clear();
}

bool MapChip::SetChipCollide(GameObject* _object)
{
	if (_object != nullptr)
	{
		ChipCollider* collider = _object->AddComponent<ChipCollider>();
		colliderList.emplace_back(collider);
		collider->map = this;
		return true;
	}
	return false;
}

GameObject* MapChip::GetChip(int _h, int _w)
{
	int i = GetIndex(_h, _w);
	if (i != -1)
	{
		return &map[i];
	}
	return nullptr;
}

int MapChip::GetIndex(int _h, int _w) const
{
	if (_h < height && _w < width)
		return _h * height + _w;
	return -1;
}

void MapChip::EraseCollider(ChipCollider* _collide)
{
	for (std::list<ChipCollider*>::iterator it = colliderList.begin(), end = colliderList.end(); it != end; ++it)
		if (*it == _collide)
		{
			colliderList.erase(it);
		}
}
