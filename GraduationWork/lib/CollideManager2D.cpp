#include "CollideManager2D.h"
#include "Collider2D.h"

CollideManager2D::CollideManager2D()
{
}

CollideManager2D::~CollideManager2D()
{
}

void CollideManager2D::Update()
{
	int i = 0;
	for (auto col_1 : colliderList) {
		++i;
		int j = 0;
		for (auto col_2 : colliderList) {
			if (++j <= i) {
				continue;	// 既に確認したオブジェクトは飛ばす
			}
			CheckCollider(col_1, col_2);
		}
	}
}

bool CollideManager2D::PushCollider(Collider2D* _col)
{
	if (_col != nullptr) {
		COL_INFO* info = new COL_INFO(_col);
		colliderList.emplace_back(info);
		return true;
	}
	return false;
}

void CollideManager2D::RemoveCollider(Collider2D* _col)
{
	// リストの中から対応したコライダーを検索し、除外
	for (auto it = colliderList.begin(); it != colliderList.end(); ++it) {
		if ((*it)->col == _col) {
			colliderList.erase(it);
			break;
		}
	}
}

void CollideManager2D::CheckCollider(COL_INFO* _col1, COL_INFO* _col2)
{
	Collider2D* col1 = _col1->col;
	Collider2D* col2 = _col2->col;

	// 既に衝突しているかを確認
	std::list<Collider2D*>::iterator itCol1;
	std::list<Collider2D*>::iterator itCol2;
	bool collided = IsCollided(_col1, col2, itCol1);
	bool collided2 = false;
	if (collided) {
		collided = IsCollided(_col2, col1, itCol2);
	}

	// 当たっているかの確認
	if (col1->IsCollide(col2)) {	// 衝突している時
		if (collided) {	// 既に衝突していたら
			// 衝突している間の関数を呼ぶ
			col1->ExecuteAllCollisionStay(col2);
			col2->ExecuteAllCollisionStay(col1);
		}
		else {	// まだ衝突していなかったら
			// 衝突した瞬間の関数を呼ぶ
			col1->ExecuteAllCollisionEnter(col2);
			col2->ExecuteAllCollisionEnter(col1);
			// 新しく衝突リストに追加
			_col1->currentCollideList.emplace_back(col2);
			_col2->currentCollideList.emplace_back(col1);
		}
	}
	else {	// 衝突していない時
		if (collided) {
			// 衝突終了の関数を呼ぶ
			col1->ExecuteAllCollisionExit(col2);
			col2->ExecuteAllCollisionExit(col1);
			// 衝突リストから外す
			_col1->currentCollideList.erase(itCol1);
			if (collided2)
				_col2->currentCollideList.erase(itCol2);
		}
	}
}

bool CollideManager2D::IsCollided(COL_INFO* _colInfo, Collider2D* _col, std::list<Collider2D*>::iterator& _it)
{
	for (auto it = _colInfo->currentCollideList.begin(); it != _colInfo->currentCollideList.end(); ++it) {
		if ((*it) == _col) {
			_it = it;
			return true;
		}
	}
	return false;
}
