#pragma once

#include <vector>
#include <list>
#include "GameObject.h"

class Chip;
class ChipCollider;

class MapChip :public GameObject
{
	friend ChipCollider;

private:
	struct Searcher
	{
		bool Search(int _type) { return (this->*search)(_type); };

		void SetG(bool (*_f)(int)) { g_search = _f; search = &Searcher::SearchG; }
		void SetO(GameObject* _obj, bool(GameObject::* _f)(int))
			{ obj = _obj; o_search = _f; search = &Searcher::SearchM; }
		void SetC(Component* _comp, bool (Component::* _f)(int))
			{ comp = _comp; c_search = _f; search = &Searcher::SearchC; }

	private:
		bool (Searcher::* search)(int);
		
		bool SearchG(int _type) { return g_search(_type); }
		bool SearchM(int _type) { return (obj->*o_search)(_type); }
		bool SearchC(int _type) { return (comp->*c_search)(_type); }
		bool (GameObject::* o_search)(int);
		bool (Component::* c_search)(int);
		bool (*g_search)(int);
		GameObject* obj;
		Component* comp;
	};

public:
	MapChip();

	~MapChip();

	void ChipUpdate();

	void PostChipUpdate();

	void CheckCollide();
	
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
	/// <param name="_xsize">横幅、マイナス値でチップのサイズを割り当てる</param>
	/// <param name="_ysize">縦幅、マイナス値でチップのサイズを割り当てる</param>
	/// <returns>true：成功、false：失敗</returns>
	bool SetChipCollider(GameObject* _object, int _xsize = -1, int _ysize = -1);

	/// <summary>
	/// 当たり判定のサイズをセット
	/// </summary>
	/// <param name="_object">セットするオブジェクト</param>
	/// <param name="_xsize">セットする横幅、マイナスでチップサイズ、nullで無視</param>
	/// <param name="_ysize">セットする縦幅、マイナスでチップサイズ、nullで無視</param>
	/// <returns>true：成功、false：オブジェクトが存在しない</returns>
	bool SetColliderSize(GameObject* _object, int* _xsize, int* _ysize);

	/// <summary>
	/// 当たり判定のサイズを取得
	/// </summary>
	/// <param name="_object">取得するオブジェクト</param>
	/// <param name="_xsize">横幅格納、nullで無視</param>
	/// <param name="_ysize">縦幅格納、nullで無視</param>
	/// <returns>true：成功、false：オブジェクトが存在しない</returns>
	bool GetColliderSize(GameObject* _object, int* _xsize, int* _ysize);

	/// <summary>
	/// チップを取得
	/// </summary>
	/// <param name="_h">チップの高さ</param>
	/// <param name="_w">チップの幅</param>
	/// <returns>null以外：チップ、null：範囲外</returns>
	Chip* GetChip(int _h, int _w);

	/// <summary>
	/// マップの高さ取得
	/// </summary>
	/// <returns>高さ</returns>
	int GetHeight()const { return height; }

	/// <summary>
	/// マップの幅取得
	/// </summary>
	/// <returns>幅</returns>
	int GetWidth()const { return width; }

	/// <summary>
	/// チップの高さ取得
	/// </summary>
	/// <returns>高さ</returns>
	int GetSizeY()const { return sizeY; }

	/// <summary>
	/// チップの幅取得
	/// </summary>
	/// <returns>幅</returns>
	int GetSizeX()const { return sizeX; }

	/// <summary>
	/// 経路探索
	/// </summary>
	/// <param name="_obj">経路探索を行うオブジェクト</param>
	/// <param name="_h">開始のY位置</param>
	/// <param name="_w">開始のX位置</param>
	/// <param name="_desH">目的地のY位置</param>
	/// <param name="_desW">目的地のX位置</param>
	/// <param name="_callObj">コールバックするオブジェクト</param>
	/// <param name="_isContinue">チップの種類が通り抜けられるか判定、戻り値・true：通れる、false：通れない</param>
	/// <param name="_outH">最端ルートの次に進むY位置</param>
	/// <param name="_outW">最端ルートの次に進むX位置</param>
	/// <returns>true：成功、false：失敗（引数が不正、たどり着かない、最端ルートは格納します）</returns>
	bool FindRoute(int _h, int _w, int _desH, int _desW, GameObject* _callObj, bool (GameObject::* _isContinue)(int), int& _outH, int& _outW);

	/// <summary>
	/// 経路探索
	/// </summary>
	/// <param name="_h">開始のY位置</param>
	/// <param name="_w">開始のX位置</param>
	/// <param name="_desH">目的地のY位置</param>
	/// <param name="_desW">目的地のX位置</param>
	/// <param name="_callComp">コールバックするコンポーネント</param>
	/// <param name="_isContinue">チップの種類が通り抜けられるか判定、戻り値・true：通れる、false：通れない</param>
	/// <param name="_outH">最端ルートの次に進むY位置</param>
	/// <param name="_outW">最端ルートの次に進むX位置</param>
	/// <returns>true：成功、false：失敗（引数が不正、たどり着かない、最端ルートは格納します）</returns>
	bool FindRoute(int _h, int _w, int _desH, int _desW, Component* _callComp, bool (Component::* _isContinue)(int), int& _outH, int& _outW);

	/// <summary>
	/// 経路探索
	/// </summary>
	/// <param name="_h">開始のY位置</param>
	/// <param name="_w">開始のX位置</param>
	/// <param name="_desH">目的地のY位置</param>
	/// <param name="_desW">目的地のX位置</param>
	/// <param name="_isContinue">チップの種類が通り抜けられるか判定、戻り値・true：通れる、false：通れない</param>
	/// <param name="_outH">最端ルートの次に進むY位置、たどり着かない場合最近点を格納</param>
	/// <param name="_outW">最端ルートの次に進むX位置、たどり着かない場合最近点を格納</param>
	/// <returns>true：成功、false：失敗（引数が不正→-1を格納します、たどり着かない→最近点を格納します）</returns>
	bool FindRoute(int _h, int _w, int _desH, int _desW, bool (*_isContinue)(int), int& _outH, int& _outW);

private:
	bool RouteSearch(int _h, int _w, int _desH, int _desW, Searcher&_searcher, int& _outH, int& _outW);

	int GetIndex(int _h, int _w)const;

	void EraseCollider(ChipCollider* _collide);

	void CheckOverlap(Chip* _chips[4]);

private:
	std::vector<Chip> map;

	std::list<ChipCollider*> colliderList;

	int height, width, sizeX, sizeY;

public:
	bool isLoopX, isLoopY;//ループして当たり判定を取るか

};
