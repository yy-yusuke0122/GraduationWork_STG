#pragma once
#include <list>

template<class T>
class CLiner4TreeManager;
template<class T>
class OBJECT_FOR_TREE;

class Collider;
class Collider2D;

class CollideManager2D {
public:
	CollideManager2D();
	~CollideManager2D();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init(unsigned int Level = 8, float left = -1000.0f, float top = -1000.0f, float right = 1000.0f, float bottom = 1000.0f);

	/// <summary>
	/// 当たり判定を確認
	/// </summary>
	void Update();

	/// <summary>
	/// Collider2Dを管理下に追加する
	/// </summary>
	/// <param name="_col">追加したいCollider</param>
	/// <returns>true:成功, false:既に登録されている</returns>
	bool PushCollider(Collider2D* _col);

	/// <summary>
	/// コライダーを管理下から外す
	/// コライダー削除時に自動で呼ばれるので、直接呼ばないこと
	/// </summary>
	void RemoveCollider(Collider2D* _col);

private:
	struct COL_PAIR {
		Collider2D* col1;
		Collider2D* col2;
		COL_PAIR(Collider2D* _col1, Collider2D* _col2) : col1(_col1), col2(_col2) {}
		~COL_PAIR() {}
	};
	std::list<COL_PAIR> currentCollideList;
	CLiner4TreeManager<Collider2D>* LTree;
	std::list<OBJECT_FOR_TREE<Collider2D>*> pOFTAry;
private:
	void CheckCollideEnter(Collider2D* _col1, Collider2D* _col2);
	bool CheckCollideStay(Collider2D* _col1, Collider2D* _col2);

	/// <summary>
	/// 既に衝突しているかを確認する
	/// 既に衝突していた場合、引数のイテレータに代入される
	/// </summary>
	/// <param name="_colInfo">確認する衝突リストを持つCOL_INFO</param>
	/// <param name="_col2">既に衝突しているか確認するコライダー</param>
	/// <param name="_it">既に衝突しているコライダーを指すイテレータ</param>
	/// <returns>既に衝突していればtrue</returns>
	//bool IsCollided(COL_INFO* _colInfo, Collider2D* _col, std::list<Collider2D*>::iterator& _it);
	bool IsCollided(Collider2D* _col1, Collider2D* _col2);
};