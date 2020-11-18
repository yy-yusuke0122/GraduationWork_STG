#include "CollideManager3D.h"
#include "Collider3D.h"

CollideManager3D::CollideManager3D()
{
}

CollideManager3D::~CollideManager3D()
{
}

void CollideManager3D::Update()
{
	int i = 0;
	for (auto col_1 : colliderList) {
		++i;
		int j = 0;
		for (auto col_2 : colliderList) {
			if (++j <= i) {
				continue;	// ���Ɋm�F�����I�u�W�F�N�g�͔�΂�
			}
			CheckCollider(col_1, col_2);
		}
	}
}

bool CollideManager3D::PushCollider(Collider3D* _col)
{
	if (_col != nullptr) {
		COL_INFO* info = new COL_INFO(_col);
		colliderList.emplace_back(info);
		return true;
	}
	return false;
}

void CollideManager3D::RemoveCollider(Collider3D* _col)
{
	// ���X�g�̒�����Ή������R���C�_�[���������A���O
	for (auto it = colliderList.begin(); it != colliderList.end(); ++it) {
		if ((*it)->col == _col) {
			colliderList.erase(it);
			break;
		}
	}
}

void CollideManager3D::CheckCollider(COL_INFO* _col1, COL_INFO* _col2)
{
	Collider3D* col1 = _col1->col;
	Collider3D* col2 = _col2->col;

	// ���ɏՓ˂��Ă��邩���m�F
	std::list<Collider3D*>::iterator itCol1;
	std::list<Collider3D*>::iterator itCol2;
	bool collided = IsCollided(_col1, col2, itCol1);
	if (collided) {
		IsCollided(_col2, col1, itCol2);
	}

	// �������Ă��邩�̊m�F
	if (col1->IsCollide(col2)) {	// �Փ˂��Ă��鎞
		if (collided) {	// ���ɏՓ˂��Ă�����
			// �Փ˂��Ă���Ԃ̊֐����Ă�
			col1->ExecuteAllCollisionStay(col2);
			col2->ExecuteAllCollisionStay(col1);
		}
		else {	// �܂��Փ˂��Ă��Ȃ�������
			// �Փ˂����u�Ԃ̊֐����Ă�
			col1->ExecuteAllCollisionEnter(col2);
			col2->ExecuteAllCollisionEnter(col1);
			// �V�����Փ˃��X�g�ɒǉ�
			_col1->currentCollideList.emplace_back(col2);
			_col2->currentCollideList.emplace_back(col1);
		}
	}
	else {	// �Փ˂��Ă��Ȃ���
		if (collided) {
			// �ՓˏI���̊֐����Ă�
			col1->ExecuteAllCollisionExit(col2);
			col2->ExecuteAllCollisionExit(col1);
			// �Փ˃��X�g����O��
			_col1->currentCollideList.erase(itCol1);
			_col2->currentCollideList.erase(itCol2);
		}
	}
}

bool CollideManager3D::IsCollided(COL_INFO* _colInfo, Collider3D* _col, std::list<Collider3D*>::iterator& _it)
{
	for (auto it = _colInfo->currentCollideList.begin(); it != _colInfo->currentCollideList.end(); ++it) {
		if ((*it) == _col) {
			_it = it;
			return true;
		}
	}
	return false;
}
