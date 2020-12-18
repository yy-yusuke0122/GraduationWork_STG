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

bool MapChip::FindRoute(int _h, int _w, int _desH, int _desW, GameObject* _callObj, bool(GameObject::* _isContinue)(int), int& _outH, int& _outW)
{
	_outH = _outW = -1;
	if (_isContinue == nullptr || _callObj == nullptr)
		return false;

	Searcher search;
	search.SetO(_callObj, _isContinue);

	return RouteSearch(_h, _w, _desH, _desW, search, _outH, _outW);
}

bool MapChip::FindRoute(int _h, int _w, int _desH, int _desW, Component* _callComp, bool(Component::* _isContinue)(int), int& _outH, int& _outW)
{
	_outH = _outW = -1;
	if (_isContinue == nullptr || _callComp == nullptr)
		return false;

	Searcher search;
	search.SetC(_callComp, _isContinue);

	return RouteSearch(_h, _w, _desH, _desW, search, _outH, _outW);
}

bool MapChip::FindRoute(int _h, int _w, int _desH, int _desW, bool(*_isContinue)(int), int& _outH, int& _outW)
{
	_outH = _outW = -1;
	if (_isContinue == nullptr)
		return false;

	Searcher search;
	search.SetG(_isContinue);

	return RouteSearch(_h, _w, _desH, _desW, search, _outH, _outW);
}

bool MapChip::RouteSearch(int _h, int _w, int _desH, int _desW, Searcher& _searcher, int& _outH, int& _outW)
{
	//範囲チェック
	if (_h >= height)_h = height - 1;
	if (_w >= width)_w = width - 1;
	if (_desH >= height)_desH = height - 1;
	if (_desW >= width)_desW = width - 1;

	//開始位置と目的地が重なっている場合終了
	if (_h == _desH && _w == _desW)
	{
		_outH = _desH;
		_outW = _desW;
		return true;
	}

	//ルート確保
	std::vector<int> route;
	route.resize(map.size());

	//目印
	int objIdx = GetIndex(_h, _w);
	int n = 0;
	for (int& r : route)
		r = -1;
	route[objIdx] = n;

	//ルートが確定してから、次のマスを探す関数を定義
	struct FindNext
	{
		std::vector<int>* route;
		MapChip* map;
		bool func(int _h, int _w, int _n, int& _outH, int& _outW)
		{
			int idx = map->GetIndex(_h, _w);
			if (idx != -1 && (*route)[idx] == _n)
			{
				if (_n == 1)
				{
					_outH = _h;
					_outW = _w;
					return true;
				}
				if (func(_h - 1, _w, _n - 1, _outH, _outW)) return true;
				if (func(_h + 1, _w, _n - 1, _outH, _outW)) return true;
				if (func(_h, _w - 1, _n - 1, _outH, _outW)) return true;
				return func(_h, _w + 1, _n - 1, _outH, _outW);
			}
			return false;
		}
	};

	bool isContinue;
	do
	{
		isContinue = false;

		for (int h = 0; h < height; ++h)
		{
			for (int w = 0; w < width; ++w)
			{
				int i = GetIndex(h, w);
				if (route[i] != n)continue;
				if (h == _desH && w == _desW)
				{
					//見つかった
					if (route[i] == 1)
					{
						//目的地と次の位置が重なっている
						_outH = _desH;
						_outW = _desW;
					}

					std::vector<int> mark;
					mark.resize(map.size());
					for (int& r : mark)r = 0;

					FindNext findNext;
					findNext.map = this;
					findNext.route = &route;

					--n;

					if (findNext.func(h - 1, w, n, _outH, _outW))return true;
					if (findNext.func(h + 1, w, n, _outH, _outW))return true;
					if (findNext.func(h, w - 1, n, _outH, _outW))return true;

					return findNext.func(h, w + 1, n, _outH, _outW);
				}

				auto check = [route, n, this](int _i, Searcher& _s) {
					return (_i != -1) && (route[_i] == -1 || route[_i] > n) && (_s.Search(this->map[_i].type)); };

				//上下左右が通れれば目印をつける
				int next = n;

				i = GetIndex(h - 1, w);
				if (check(i, _searcher))next = route[i] = n + 1;

				i = GetIndex(h + 1, w);
				if (check(i, _searcher))next = route[i] = n + 1;

				i = GetIndex(h, w - 1);
				if (check(i, _searcher))next = route[i] = n + 1;

				i = GetIndex(h, w + 1);
				if (check(i, _searcher))next = route[i] = n + 1;

				if (n != next)
				{
					isContinue = true;
				}
			}
		}

		++n;

	} while (isContinue);

	//見つからなかった場合、最近点を見つける
	int disH, disW, outH, outW;
	auto absi = [](int _i) {return (_i > 0) ? _i : -_i; };
	disH = absi(_h - _desH);
	disW = absi(_w - _desW);
	outH = _h;
	outW = _w;
	for (int h = 0; h < height; ++h)
	{
		for (int w = 0; w < width; ++w)
		{
			if (route[GetIndex(h, w)] == -1)continue;

			int judgeH = absi(_desH - h);
			int judgeW = absi(_desW - w);
			if (judgeH + judgeW < disH + disW)
			{
				disH = judgeH;
				disW = judgeW;
				outH = h;
				outW = w;
			}
		}
	}

	_outH = outH;
	_outW = outW;
	
	return false;
}

int MapChip::GetIndex(int _h, int _w) const
{
	if ((_h >= 0 && _w >= 0) && (_h < height && _w < width))
		return _h * width + _w;
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
