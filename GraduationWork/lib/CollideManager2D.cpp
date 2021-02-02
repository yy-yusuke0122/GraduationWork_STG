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
		(*it)->Remove();
		it = pOFTAry.erase(it);
	}
}

void CollideManager2D::Init()
{
	LTree->Init(8, -100.0f, -100.0f, 1000 + 100.0f, 700 + 100.0f);
	RemoveAll();
}

void CollideManager2D::Update()
{
	if (pOFTAry.size() > 0) {
		// ���[�v���ꎞ�ϐ�
		DWORD ColNum;				// �Փ˔����
		CollisionList<Collider2D>* ColVect;	// �ՓˑΏۃ��X�g

		//�X�V���Cell���ēo�^
		for (auto oft : pOFTAry) {
			Collider2D* col = oft->m_pObject;

			// �ēo�^
			AABB2D aabb = col->GetAABB2D();
			Point2D lt = aabb.LeftTop();
			Point2D rb = aabb.RightBottom();
			LTree->Regist(lt.x, lt.y, rb.x, rb.y, oft);
		}

		// �O�t���[���ɏՓ˂��Ă�����̓��m�ŏՓ˔���
		for (std::list<COL_PAIR>::iterator it = currentCollideList.begin(); it != currentCollideList.end();) {
			if (CheckCollideStay(it->col1, it->col2)) {
				it = currentCollideList.erase(it);
			}
			else {
				++it;
			}
		}

		// �ՓˑΉ����X�g���擾
		ColNum = LTree->GetAllCollisionList(&ColVect);

		// �Փ˔���
		DWORD c;
		if (ColNum != 12)
			int a = 0;
		ColNum /= 2;	// 2�Ŋ���̂̓y�A�ɂȂ��Ă���̂�
		Collider2D** p = ColVect->getRootPtr();
		Collider2D* pRoot[10000];
		for (int i = 0; i < ColNum; ++i) {
			pRoot[i] = p[i];
		}
		for (c = 0; c < ColNum; c++) {
			// �����R���C�_�[���m�͔�����s��Ȃ�
			if (p[c * 2] == p[c * 2 + 1])
				continue;

			// �Փˊm�F
			CheckCollideEnter(p[c * 2], p[c * 2 + 1]);
		}
	}
	
	//int i = 0;
	//for (auto col_1 : colliderList) {
	//	++i;
	//	int j = 0;
	//	for (auto col_2 : colliderList) {
	//		if (++j <= i) {
	//			continue;	// ���Ɋm�F�����I�u�W�F�N�g�͔�΂�
	//		}
	//		CheckCollider(col_1, col_2);
	//	}
	//}
}

void CollideManager2D::RemoveAll()
{
	for (std::list<OBJECT_FOR_TREE<Collider2D>*>::iterator it = pOFTAry.begin(); it != pOFTAry.end();) {
		(*it)->Remove();
		it = pOFTAry.erase(it);
	}
	pOFTAry.clear();

	for (std::list<COL_PAIR>::iterator it = currentCollideList.begin(); it != currentCollideList.end();) {
		it = currentCollideList.erase(it);
	}
	currentCollideList.clear();
}

bool CollideManager2D::PushCollider(Collider2D* _col)
{
	// OFT�ɓo�^
	OBJECT_FOR_TREE<Collider2D>* p = new OBJECT_FOR_TREE<Collider2D>();
	p->m_pObject = _col;	// �o�^
	pOFTAry.emplace_back(p);

	return true;

	/*if (_col != nullptr) {
		COL_INFO* info = new COL_INFO(_col);
		colliderList.emplace_back(info);
		return true;
	}
	return false;*/
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
	//// ���X�g�̒�����Ή������R���C�_�[���������A���O
	//for (auto it = colliderList.begin(); it != colliderList.end(); ++it) {
	//	if ((*it) == _col) {
	//		colliderList.erase(it);
	//		break;
	//	}
	//}
}

void CollideManager2D::CheckCollideEnter(Collider2D* _col1, Collider2D* _col2)
{
	// �O�t���[���ɏՓ˂��Ă�����̓��m�̔���͍s��Ȃ�
	if (IsCollided(_col1, _col2))
		return;

	if (_col1->IsCollide(_col2)) {
		// �Փ˂����u�Ԃ̊֐����Ă�
		_col1->ExecuteAllCollisionEnter(_col2);
		_col2->ExecuteAllCollisionEnter(_col1);
		// �V�����Փ˃��X�g�ɒǉ�
		COL_PAIR colPair(_col1, _col2);
		currentCollideList.push_back(colPair);
	}
}

bool CollideManager2D::CheckCollideStay(Collider2D* _col1, Collider2D* _col2)
{
	if (_col1->IsCollide(_col2)) {
		// �Փ˒��̊֐����Ă�
		_col1->ExecuteAllCollisionStay(_col2);
		_col2->ExecuteAllCollisionStay(_col1);
		return true;
	}
	else {
		// �ՓˏI���̊֐����Ă�
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
