#include "ChipCollider.h"
#include "Chip.h"
#include "MapChipManager.h"
#include "UrLib.h"

namespace
{
	const std::string NAME = "Chip_";
	const char* CLASS_NAME = typeid(Chip).name();
}

MapChip::MapChip() :
	height(1), width(1), sizeX(1), sizeY(1), isLoopX(false), isLoopY(false)
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

void MapChip::ChipUpdate()
{
	for (size_t i = 0ull, size = map.size(); i < size; ++i)
		map[i].Update();
}

void MapChip::PostChipUpdate()
{
	for (size_t i = 0ull, size = map.size(); i < size; ++i)
		map[i].PostUpdate();
}

void MapChip::CheckCollide()
{
	for (std::list<ChipCollider*>::iterator it = colliderList.begin(), end = colliderList.end(); it != end; ++it)
	{
		ChipCollider* collider = (*it);
		GameObject* obj = collider->gameObject;
		Transform* trans = collider->transform;

		int x = static_cast<int>(trans->position.x);
		int y = static_cast<int>(trans->position.y);

		int hx = collider->sizeX / 2;
		int hy = collider->sizeY / 2;

		int lx = x - hx;
		int rx = x + hx;
		int uy = y - hy;
		int dy = y + hy;

		int  left = lx / sizeX;
		int	   up = uy / sizeY;
		int right = rx / sizeX;
		int  down = dy / sizeY;

		//関数定義

		//ループしないときの関数
		auto mincheck = [](int& _i, float& _pos, int _hsize)
		{
			if (_pos < _hsize)
			{
				_i = 0;
				_pos = static_cast<float>(_hsize);
				return true;
			}
			return false;
		};

		auto maxcheck = [](int& _i, int _max, float& _pos, int _size, int _hsize)
		{
			if (_i >= _max)
			{
				_i = _max - 1;
				_pos = static_cast<float>(_max * _size - _hsize);
				return true;
			}
			return false;
		};

		auto nonloop = [mincheck, maxcheck] (
			int& _minIdx, int& _maxIdx, int _size, float& _pos, int _chipsize, int _hsize)
		{
			if (mincheck(_minIdx, _pos, _hsize)) ++_maxIdx;
			else 
				if (maxcheck(_maxIdx, _size, _pos, _chipsize, _hsize))
				{
					if (_maxIdx > 0)_minIdx = _maxIdx - 1;
					else _minIdx = 0;
				}
		};

		//ループ時の関数
		auto plusloop = [](int& _i, int _size) { _i %= _size; };

		auto minusloop = [plusloop](int& _i, int _pos, int _size)
		{
			--_i;
			plusloop(_i, _size);
			if (_i < 0)
				_i += _size;
		};

		auto signcheck = [minusloop, plusloop](int& _i, int _pos, int _size)
		{
			if (_pos < 0)
				minusloop(_i, _pos, _size);
			else
				plusloop(_i, _size);
		};

		auto loop = [signcheck](int& _minIdx, int& _maxIdx, int _minpos, int _maxpos, int _size)
		{
			signcheck(_minIdx, _minpos, _size);
			signcheck(_maxIdx, _maxpos, _size);
		};

		//マップチップ処理
		auto checkloop = [loop, nonloop](bool _loop, int& _minIdx, int& _maxIdx,
			int _minpos, int _maxpos, int _size, float& _pos, int _chipsize, int _hsize)
		{
			if (_loop) loop(_minIdx, _maxIdx, _minpos, _maxpos, _size);
			else	nonloop(_minIdx, _maxIdx, _size, _pos, _chipsize, _hsize);
		};

		//マップチップの縦横判定
		checkloop(isLoopX, left, right, lx, rx, width, trans->position.x, sizeX, hx);
		checkloop(isLoopY, up, down, uy, dy, height, trans->position.y, sizeY, hy);

		Chip* chips[4]{};

		//当たっているチップを格納
		chips[0] = &map[GetIndex(  up,  left)];
		chips[1] = &map[GetIndex(  up, right)];
		chips[2] = &map[GetIndex(down,  left)];
		chips[3] = &map[GetIndex(down, right)];

		//重複削除
		CheckOverlap(chips);

		//Stay呼出し
		for (Chip*& p : chips)
		{
			if (p == nullptr)continue;

			//当たっていた場合は即終了
			if (collider->CheckCollide(p))
				p = nullptr;
		}

		//Exit呼出し
		collider->ClearChip();//当たっていないチップを消す

		//Enter呼出し
		for (Chip* p : chips)
		{
			//初めて当たった場合は追加
			if (p != nullptr)
				collider->AddChip(p);
		}
	}
}

bool MapChip::Create(int _height, int _width, int _sizeX, int _sizeY)
{
	if (map.size() != 0ull)return false;

	if (_height > 0)
		height = _height;
	if (_width > 0)
		width = _width;
	if (_sizeX > 0)
		sizeX = _sizeX;
	if (_sizeY > 0)
		sizeY = _sizeY;

	VECTOR2 hs(static_cast<float>(sizeX) / 2.f, static_cast<float>(sizeY) / 2.f);

	map.resize(static_cast<size_t>(_height) * static_cast<size_t>(_width));
	for (int h = 0; h < height; ++h)
	{ 
		std::string hname = NAME + std::to_string(h) + "_";
		for (int w = 0; w < width; ++w)
		{
			int i = GetIndex(h, w);
			map[i].tag = hname + std::to_string(w);
			map[i].className = CLASS_NAME;
			map[i].map = this;
			map[i].h = h;
			map[i].w = w;
			map[i].SetParent(this);
			map[i].scene = GetScene();
			map[i].transform->position =
				VECTOR3(static_cast<float>(w * sizeX) + hs.x, static_cast<float>(h * sizeY) + hs.y, 0);
		}
	}
	return true;
}

void MapChip::Clear()
{
	map.clear();
}

bool MapChip::SetChipCollider(GameObject* _object, int _xsize, int _ysize)
{
	if (_object == nullptr)return false;

	ChipCollider* collider = _object->AddComponent<ChipCollider>();
	if (collider == nullptr)return false;

	if (_xsize == -1)_xsize = sizeX;
	if (_ysize == -1)_ysize = sizeY;

	collider->sizeX = sizeX;
	collider->sizeY = sizeY;
	collider->map = this;

	colliderList.emplace_back(collider);

	return true;
}

bool MapChip::SetColliderSize(GameObject* _object, int* _xsize, int* _ysize)
{
	for (ChipCollider* p : colliderList)
	{
		if (p->gameObject != _object)continue;

		auto f = [](int&_current,int*_set,int _chip) 
		{
			if (_set == nullptr)return;
			if (*_set < 0)_current = _chip;
			else _current = *_set;
		};

		f(p->sizeX, _xsize, sizeX);
		f(p->sizeY, _ysize, sizeY);
		return true;
	}
	return false;
}

bool MapChip::GetColliderSize(GameObject* _object, int* _xsize, int* _ysize)
{
	for (ChipCollider* p : colliderList)
	{
		if (p->gameObject != _object)continue;

		if (_xsize != nullptr)*_xsize = p->sizeX;
		if (_ysize != nullptr)*_ysize = p->sizeY;
		return true;
	}
	return false;
}

Chip* MapChip::GetChip(int _h, int _w)
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
		if ((*it) == _collide)
		{
			colliderList.erase(it);
		}
}
void MapChip::CheckOverlap(Chip* _chips[4])
{
	//重複チェック
	for (int i = 0; i < 4; ++i)
	{
		if (_chips[i] == nullptr)continue;

		for (int j = i + 1; j < 4; ++j)
		{
			if (_chips[j] == nullptr)continue;

			if ((_chips[i]->GetH() == _chips[j]->GetH()) &&
				(_chips[i]->GetW() == _chips[j]->GetW()))
				_chips[j] = nullptr;
		}
	}
}
