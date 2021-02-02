#include "CollideManager2D.h"
#include "Collider2D.h"
#include "CollideClass.h"

CollideManager2D::CollideManager2D()
{
	LTree = new CLiner4TreeManager<Collider2D>();
	pOFTAry.clear();
	currentCollideList.clear();
}

CollideManager2D::~CollideManager2D()
{
	delete LTree;

	for (std::list<OBJECT_FOR_TREE<Collider2D>*>::iterator it = pOFTAry.begin(); it != pOFTAry.end();) {
		delete (*it);
		it = pOFTAry.erase(it);
	}
}

void CollideManager2D::Init(unsigned int Level, float left, float top, float right, float bottom)
{
	LTree->Init(Level, left, top, right, bottom);

	for (std::list<OBJECT_FOR_TREE<Collider2D>*>::iterator it = pOFTAry.begin(); it != pOFTAry.end();) {
		delete (*it);
		it = pOFTAry.erase(it);
	}
	pOFTAry.clear();
	currentCollideList.clear();
}

void CollideManager2D::Update()
{
	if (pOFTAry.size() > 0) {
		// ループ内一時変数
		DWORD ColNum;				// 衝突判定回数
		CollisionList<Collider2D>* ColVect;	// 衝突対象リスト

		//更新後のCellを再登録
		for (auto oft : pOFTAry) {
			Collider2D* col = oft->m_pObject;

			// 再登録
			AABB2D aabb = col->GetAABB2D();
			Point2D lt = aabb.LeftTop();
			Point2D rb = aabb.RightBottom();
			LTree->Regist(lt.x, lt.y, rb.x, rb.y, oft);
		}

		// 前フレームに衝突しているもの同士で衝突判定
		for (std::list<COL_PAIR>::iterator it = currentCollideList.begin(); it != currentCollideList.end();) {
			if (!CheckCollideStay(it->col1, it->col2)) {
				it = currentCollideList.erase(it);
			}
			else {
				++it;
			}
		}

		// 衝突対応リストを取得
		ColNum = LTree->GetAllCollisionList(&ColVect);

		// 衝突判定
		DWORD c;
		ColNum /= 2;	// ペアになっているので2で割る
		Collider2D** p = ColVect->getRootPtr();
		Collider2D* pRoot[10000];
		for (int i = 0; i < ColNum; ++i) {
			pRoot[i] = p[i];
		}
		for (c = 0; c < ColNum; c++) {
			// 同じコライダー同士は判定を行わない
			if (p[c * 2] == p[c * 2 + 1])
				continue;

			// 衝突確認
			CheckCollideEnter(p[c * 2], p[c * 2 + 1]);
		}
	}
}

bool CollideManager2D::PushCollider(Collider2D* _col)
{
	// OFTに登録
	OBJECT_FOR_TREE<Collider2D>* p = new OBJECT_FOR_TREE<Collider2D>();
	p->m_pObject = _col;	// 登録
	pOFTAry.emplace_back(p);

	return true;
}

void CollideManager2D::RemoveCollider(Collider2D* _col)
{
	for (std::list<COL_PAIR>::iterator it = currentCollideList.begin(); it != currentCollideList.end();) {
		if ((*it).col1 == _col || (*it).col2 == _col) {
			it = currentCollideList.erase(it);
		}
		else {
			++it;
		}
	}

	for (std::list<OBJECT_FOR_TREE<Collider2D>*>::iterator it = pOFTAry.begin(); it != pOFTAry.end();) {
		if ((*it)->m_pObject == _col) {
			(*it)->Remove();
			it = pOFTAry.erase(it);
			return;
		}
		else {
			++it;
		}
	}
}

void CollideManager2D::CheckCollideEnter(Collider2D* _col1, Collider2D* _col2)
{
	// 前フレームに衝突しているもの同士の判定は行わない
	if (IsCollided(_col1, _col2))
		return;

	if (_col1->IsCollide(_col2)) {
		// 衝突した瞬間の関数を呼ぶ
		_col1->ExecuteAllCollisionEnter(_col2);
		_col2->ExecuteAllCollisionEnter(_col1);
		// 新しく衝突リストに追加
		COL_PAIR colPair(_col1, _col2);
		currentCollideList.push_back(colPair);
	}
}

bool CollideManager2D::CheckCollideStay(Collider2D* _col1, Collider2D* _col2)
{
	if (_col1->IsCollide(_col2)) {
		// 衝突中の関数を呼ぶ
		_col1->ExecuteAllCollisionStay(_col2);
		_col2->ExecuteAllCollisionStay(_col1);
		return true;
	}
	else {
		// 衝突終了の関数を呼ぶ
		_col1->ExecuteAllCollisionExit(_col2);
		_col2->ExecuteAllCollisionExit(_col1);
	}

	return false;
}

bool CollideManager2D::IsCollided(Collider2D* _col1, Collider2D* _col2)
{
	for (auto pair : currentCollideList) {
		if ((_col1 == pair.col1 && _col2 == pair.col2) ||
			(_col2 == pair.col1 && _col1 == pair.col2)) {
			return true;
		}
	}

	return false;
}
