#pragma once
#include <list>

class Collider;
class Collider2D;

class CollideManager2D {
public:
	CollideManager2D();
	~CollideManager2D();

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
	struct COL_INFO {
		Collider2D* col;
		std::list<Collider2D*> currentCollideList;
		COL_INFO(Collider2D* _col) : col(_col) {}
		~COL_INFO() {}
	};
	std::list<COL_INFO*> colliderList;
private:
	/// <summary>
	/// お互いが衝突しているかを確認し、
	/// 衝突時は対応した関数を呼ぶ
	/// </summary>
	void CheckCollider(COL_INFO* _col1, COL_INFO* _col2);

	/// <summary>
	/// 既に衝突しているかを確認する
	/// 既に衝突していた場合、引数のイテレータに代入される
	/// </summary>
	/// <param name="_colInfo">確認する衝突リストを持つCOL_INFO</param>
	/// <param name="_col2">既に衝突しているか確認するコライダー</param>
	/// <param name="_it">既に衝突しているコライダーを指すイテレータ</param>
	/// <returns>既に衝突していればtrue</returns>
	bool IsCollided(COL_INFO* _colInfo, Collider2D* _col, std::list<Collider2D*>::iterator& _it);
};