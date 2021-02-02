#pragma once
#include "typedef.h"
#include <list>

template <class T>
class CCell;
/////////////////////////////////////
// ���ؓo�^�I�u�W�F�N�g(OFT)
//////////////////////////////////
template< class T>
class OBJECT_FOR_TREE
{
public:
	CCell<T>* m_pCell;			// �o�^���
	T* m_pObject;				// ����ΏۃI�u�W�F�N�g
	OBJECT_FOR_TREE<T>* m_pPre;	// �O��OBJECT_FOR_TREE�\����
	OBJECT_FOR_TREE<T>* m_pNext;	// ����OBJECT_FOR_TREE�\����
	int m_id;

public:
	OBJECT_FOR_TREE(int id = 0) {
		m_id = id;
		m_pCell = nullptr;
		m_pObject = nullptr;
		m_pPre = nullptr;
		m_pNext = nullptr;
	}

	virtual ~OBJECT_FOR_TREE()
	{
	}

public:
	// ���烊�X�g����O���
	bool Remove() {
		// ���łɈ�E���Ă��鎞�͏����I��
		if (!m_pCell)
			return false;

		// ������o�^���Ă����ԂɎ��g��ʒm
		if (!m_pCell->OnRemove(this))
			return false;

		// ��E����
		// �O��̃I�u�W�F�N�g�����т���
		if (m_pPre != nullptr)
		{
			m_pPre->m_pNext = m_pNext;
		}
		if (m_pNext != nullptr)
		{
			m_pNext->m_pPre = m_pPre;
		}
		m_pPre = nullptr;
		m_pNext = nullptr;
		m_pCell = nullptr;
		return true;
	}

};


/////////////////////////////////////
// �Փ˃��X�g
//////////////////////////////////
#define COLLISIONLIST_REALLOCSIZE	100
template < class T >
class CollisionList {
public:
	CollisionList() : root_(nullptr), pos_(0), mallocSize_(0) {
		root_ = (T**)malloc(0);
	}
	~CollisionList() {
		reflesh();
	}

	size_t getSize() {
		return pos_;
	}

	T** getRootPtr() {
		return root_;
	}

	void resetPos() {
		pos_ = 0;
	}

	void wright(T* obj1, T* obj2) {
		if (pos_ >= mallocSize_) {
			root_ = (T**)realloc(root_, sizeof(T*) * (mallocSize_ + COLLISIONLIST_REALLOCSIZE));
			mallocSize_ += COLLISIONLIST_REALLOCSIZE;
		}
		root_[pos_++] = obj1;
		root_[pos_++] = obj2;
	}

	void reflesh() {
		if (root_) {
			free(root_);
		}
	}

private:
	T** root_;		// ���X�g���[�g�|�C���^
	size_t	pos_;
	size_t	mallocSize_;
};

/////////////////////////////////////
// ���`4���؋�ԊǗ��N���X
//////////////////////////////////
#define CLINER4TREEMANAGER_MAXLEVEL		9
template <class T>
class CLiner4TreeManager
{
protected:
	unsigned int m_uiDim;
	CCell<T>** ppCellAry;	// ���`��ԃ|�C���^�z��
	unsigned int m_iPow[CLINER4TREEMANAGER_MAXLEVEL + 1];	// �ׂ��搔�l�z��
	float m_fW;		// �̈��X����
	float m_fH;		// �̈��Y����
	float m_fLeft;	// �̈�̍����iX���ŏ��l�j
	float m_fTop;	// �̈�̏㑤�iY���ŏ��l�j
	float m_fUnit_W;		// �ŏ����x����Ԃ̕��P��
	float m_fUnit_H;		// �ŏ����x����Ԃ̍��P��
	DWORD m_dwCellNum;		// ��Ԃ̐�
	unsigned int m_uiLevel;			// �ŉ��ʃ��x��
	CollisionList< T > m_ColList;	// �Փ˃��X�g

public:
	// �R���X�g���N�^
	CLiner4TreeManager()
	{
		m_uiLevel = 0;
		m_fW = 0.0f;
		m_fH = 0.0f;
		m_fLeft = 0.0f;
		m_fTop = 0.0f;
		m_fUnit_W = 0.0f;
		m_fUnit_H = 0.0f;
		m_dwCellNum = 0;
		ppCellAry = nullptr;
		m_uiDim = 0;

		// �e���x���ł̋�Ԑ����Z�o
		int i;
		m_iPow[0] = 1;
		for (i = 1; i < CLINER4TREEMANAGER_MAXLEVEL + 1; i++)
			m_iPow[i] = m_iPow[i - 1] * 4;
	}

	// �f�X�g���N�^
	virtual ~CLiner4TreeManager()
	{
		DWORD i;
		for (i = 0; i < m_dwCellNum; i++) {
			if (ppCellAry[i] != nullptr)
				delete ppCellAry[i];
		}
		delete[] ppCellAry;
	}

	// ���`4���ؔz����\�z����
	bool Init(unsigned int Level, float left, float top, float right, float bottom)
	{
		// �ݒ�ō����x���ȏ�̋�Ԃ͍��Ȃ�
		if (Level >= CLINER4TREEMANAGER_MAXLEVEL)
			return false;

		// Level���x���i0��_�j�̔z��쐬
		m_dwCellNum = (m_iPow[Level + 1] - 1) / 3;
		ppCellAry = new CCell<T> * [m_dwCellNum];
		ZeroMemory(ppCellAry, sizeof(CCell<T>*) * m_dwCellNum);

		// �̈��o�^
		m_fLeft = left;
		m_fTop = top;
		m_fW = right - left;
		m_fH = bottom - top;
		m_fUnit_W = m_fW / (1 << Level);
		m_fUnit_H = m_fH / (1 << Level);

		m_uiLevel = Level;

		return true;
	}

	// �I�u�W�F�N�g��o�^����
	bool Regist(float left, float top, float right, float bottom, OBJECT_FOR_TREE<T>* pOFT)
	{
		// �I�u�W�F�N�g�̋��E�͈͂���o�^���[�g���ԍ����Z�o
		DWORD Elem = GetMortonNumber(left, top, right, bottom);
		if (Elem < m_dwCellNum) {
			// ��Ԃ������ꍇ�͐V�K�쐬
			if (!ppCellAry[Elem])
				CreateNewCell(Elem);
			return ppCellAry[Elem]->Push(pOFT);
		}
		return false;	// �o�^���s
	}

	// �Փ˔��胊�X�g���쐬����
	DWORD GetAllCollisionList(CollisionList<T>** colList)
	{
		// ���X�g�i�z��j�͕K�����������܂�
		m_ColList.resetPos();

		// ���[�g��Ԃ̑��݂��`�F�b�N
		if (ppCellAry == nullptr)
			return 0;	// ��Ԃ����݂��Ă��Ȃ�

		// ���[�g��Ԃ�����
		std::list<T*> ColStac;
		GetCollisionList(0, ColStac);

		*colList = &m_ColList;

		return (DWORD)m_ColList.getSize();
	}



protected:

	// ��ԓ��ŏՓ˃��X�g���쐬����
	bool GetCollisionList(DWORD Elem, std::list<T*>& ColStac)
	{
		typename std::list<T*>::iterator it;
		// �@ ��ԓ��̃I�u�W�F�N�g���m�̏Փ˃��X�g�쐬
		OBJECT_FOR_TREE<T>* pOFT1 = ppCellAry[Elem]->GetFirstObj();
		
		while (pOFT1 != nullptr)
		{
			OBJECT_FOR_TREE<T>* pOFT2 = pOFT1->m_pNext;
			while (pOFT2 != nullptr) {
				m_ColList.wright(pOFT1->m_pObject, pOFT2->m_pObject);
				pOFT2 = pOFT2->m_pNext;
			}
			// �A �Փ˃X�^�b�N�Ƃ̏Փ˃��X�g�쐬
			for (it = ColStac.begin(); it != ColStac.end(); it++) {
				m_ColList.wright(pOFT1->m_pObject, *it);
			}
			pOFT1 = pOFT1->m_pNext;
		}

		bool ChildFlag = false;
		// �B �q��ԂɈړ�
		DWORD ObjNum = 0;
		DWORD i, NextElem;
		for (i = 0; i < 4; i++) {
			NextElem = Elem * 4 + 1 + i;
			if (NextElem < m_dwCellNum && ppCellAry[Elem * 4 + 1 + i]) {
				if (!ChildFlag) {
					// �C �o�^�I�u�W�F�N�g���X�^�b�N�ɒǉ�
					pOFT1 = ppCellAry[Elem]->GetFirstObj();
					while (pOFT1 != nullptr) {
						ColStac.push_back(pOFT1->m_pObject);
						ObjNum++;
						pOFT1 = pOFT1->m_pNext;
					}
				}
				ChildFlag = true;
				GetCollisionList(Elem * 4 + 1 + i, ColStac);	// �q��Ԃ�
			}
		}

		// �D �X�^�b�N����I�u�W�F�N�g���O��
		if (ChildFlag) {
			for (i = 0; i < ObjNum; i++)
				ColStac.pop_back();
		}

		return true;
	}


	// ��Ԃ𐶐�
	bool CreateNewCell(DWORD Elem)
	{
		// �����̗v�f�ԍ�
		while (!ppCellAry[Elem])
		{
			// �w��̗v�f�ԍ��ɋ�Ԃ�V�K�쐬
			ppCellAry[Elem] = new CCell<T>;

			// �e��ԂɃW�����v
			Elem = (Elem - 1) >> 2;
			if (Elem >= m_dwCellNum) break;
		}
		return true;
	}

	// ���W�����Ԕԍ����Z�o
	DWORD GetMortonNumber(float left, float top, float right, float bottom)
	{
		// �ŏ����x���ɂ�����e���ʒu���Z�o
		DWORD LT = GetPointElem(left, top);
		DWORD RB = GetPointElem(right, bottom);

		// ��Ԕԍ��̔r���I�_���a����
		// �������x�����Z�o
		DWORD Def = RB ^ LT;
		unsigned int HiLevel = 0;
		unsigned int i;
		for (i = 0; i < m_uiLevel; i++)
		{
			DWORD Check = (Def >> (i * 2)) & 0x3;
			if (Check != 0)
				HiLevel = i + 1;
		}
		DWORD SpaceNum = RB >> (HiLevel * 2);
		DWORD AddNum = (m_iPow[m_uiLevel - HiLevel] - 1) / 3;
		SpaceNum += AddNum;

		if (SpaceNum > m_dwCellNum)
			return 0xffffffff;

		return SpaceNum;
	}

	// �r�b�g�����֐�
	DWORD BitSeparate32(DWORD n)
	{
		n = (n | (n << 8)) & 0x00ff00ff;
		n = (n | (n << 4)) & 0x0f0f0f0f;
		n = (n | (n << 2)) & 0x33333333;
		return (n | (n << 1)) & 0x55555555;
	}

	// 2D���[�g����Ԕԍ��Z�o�֐�
	WORD Get2DMortonNumber(WORD x, WORD y)
	{
		return (WORD)(BitSeparate32(x) | (BitSeparate32(y) << 1));
	}

	// ���W�����`4���ؗv�f�ԍ��ϊ��֐�
	DWORD GetPointElem(float pos_x, float pos_y)
	{
		return Get2DMortonNumber((WORD)((pos_x - m_fLeft) / m_fUnit_W), (WORD)((pos_y - m_fTop) / m_fUnit_H));
	}
};


/////////////////////////////////////
// ��ԃN���X
//////////////////////////////////
template <class T>
class CCell
{
protected:
	OBJECT_FOR_TREE<T>* m_pLatest;	// �ŐVOFL�ւ̃X�}�[�g�|�C���^

public:
	// �R���X�g���N�^
	CCell() : m_pLatest(nullptr)
	{
	}

	// �f�X�g���N�^
	virtual ~CCell()
	{
		if (m_pLatest != nullptr)
			ResetLink(m_pLatest);
	}

	// �����N��S�ă��Z�b�g����
	void ResetLink(OBJECT_FOR_TREE<T>* pOFT)
	{
		if (pOFT->m_pNext != nullptr) {
			ResetLink(pOFT->m_pNext);
		}
		pOFT = nullptr;
	}

	// OFT���v�b�V��
	bool Push(OBJECT_FOR_TREE<T>* pOFT)
	{
		if (pOFT == nullptr) return false;	// �����I�u�W�F�N�g�͓o�^���Ȃ�
		if (pOFT->m_pCell == this) return false;	// 2�d�o�^�`�F�b�N
		if (m_pLatest == nullptr) {
			m_pLatest = pOFT;	// ��ԂɐV�K�o�^
		}
		else
		{
			// �ŐVOFT�I�u�W�F�N�g���X�V
			pOFT->m_pNext = m_pLatest;
			m_pLatest->m_pPre = pOFT;
			m_pLatest = pOFT;
		}
		pOFT->m_pCell = this;	// ��Ԃ�o�^
		return true;
	}

	OBJECT_FOR_TREE<T>* GetFirstObj()
	{
		return m_pLatest;
	}

	// �폜�����I�u�W�F�N�g���`�F�b�N
	bool OnRemove(OBJECT_FOR_TREE<T>* pRemoveObj)
	{
		if (m_pLatest == pRemoveObj) {
			// ���̃I�u�W�F�N�g�ɑ}���ւ�
			if (m_pLatest != nullptr)
				m_pLatest = m_pLatest->m_pNext;
		}
		return true;
	}
};
