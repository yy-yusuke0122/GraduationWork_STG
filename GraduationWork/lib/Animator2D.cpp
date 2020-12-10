#include "Animator2D.h"
#include "ImageRenderer.h"
#include "Time.h"
#include "Function.h"

//Animator2D::Animator2D() :
//	controller(nullptr), imageRenderer(nullptr), currentAnim(nullptr), currentAnimName(""), nextAnimName(""), animCount(0.0f), drawNum(0)
//{
//	animList.clear();
//}

Animator2D::Animator2D()
{
}

Animator2D::~Animator2D()
{
}

void Animator2D::Start()
{
}

void Animator2D::Update()
{
	//if (controller == nullptr)
	//	return;

	//if (imageRenderer == nullptr) {
	//	imageRenderer = GetComponent<ImageRenderer>();
	//	if (imageRenderer == nullptr)
	//		return;
	//}

	//// �A�j���[�V�����؂�ւ�
	//TransAnimation();

	//// �Đ����̃A�j���[�V������������ΏI��
	//if (currentAnim == nullptr)
	//	return;

	//// �A�j���[�V��������
	//animCount += currentAnim->speed * Time::DeltaTime();
	//if (animCount >= 1.0f) {
	//	animCount = 0.0f;
	//	if (++drawNum > currentAnim->end) {
	//		drawNum = currentAnim->start;
	//	}
	//	imageRenderer->SetImageNumber(drawNum);
	//}
}

//bool Animator2D::AddAnim(unsigned int _start, unsigned int _end, std::string _animName, float _animSpeed, bool _isLoop)
//{
//	// ���ɒǉ�����Ă���ΏI��
//	if (GetAnim(_animName) != nullptr)
//		return false;
//
//	// �A�j���[�V�����𐶐����A�ǉ�����
//	Anim2D* newAnim = new Anim2D(_start, _end, _animName, _animSpeed, _isLoop);
//	animList.push_back(newAnim);
//
//	return true;
//}
//
//bool Animator2D::DeleteAnim(std::string _animName)
//{
//	for (auto it = animList.begin(); it != animList.end();) {
//		if ((*it)->name == _animName) {
//			delete (*it);
//			it = animList.erase(it);
//			return true;
//		}
//		else {
//			++it;
//		}
//	}
//
//	return false;
//}
//
//bool Animator2D::SetStartAnim(std::string _animName)
//{
//	// ���ɒǉ�����Ă���ΏI��
//	if (GetAnim(_animName) == nullptr)
//		return false;
//
//	nextAnimName = _animName;
//	return true;
//}
//
//Anim2D* Animator2D::GetAnim(std::string _animName)
//{
//	for (auto anim : animList) {
//		if (anim->name == _animName) {
//			return anim;
//		}
//	}
//
//	return nullptr;
//}
//
//Anim2D* Animator2D::GetCurrentAnim()
//{
//	return currentAnim;
//}
//
//int Animator2D::GetDrawNum() const
//{
//	return drawNum;
//}
//
//bool Animator2D::SetDrawNum(unsigned int _num)
//{
//	if (IsInSideValue(_num, currentAnim->start, currentAnim->end + 1)) {
//		drawNum = _num;
//		return true;
//	}
//
//	return false;
//}
//
//bool Animator2D::GetBool(std::string _boolName)
//{
//	for (auto it : boolList) {
//		if (it->boolName == _boolName) {
//			return it->enable;
//		}
//	}
//	return false;
//}
//
//void Animator2D::SetBool(std::string _boolName, bool _bool)
//{
//	for (auto it : boolList) {
//		if (it->boolName == _boolName) {
//			it->enable = _bool;
//		}
//	}
//}
//
//bool Animator2D::CreateBool(std::string _boolName)
//{
//	// �������̂�AnimBool����������I��������
//	for (auto it : boolList) {
//		if (it->boolName == _boolName)
//			return false;
//	}
//
//	// �V�����J�ڗpBool�𐶐�
//	TransBool* newBool = new TransBool(_boolName);
//	boolList.emplace_back(newBool);
//
//	return true;
//}
//
//bool Animator2D::CreateTransDirection(std::string _sourceName, std::string _dirName)
//{
//	// ����TransDirection����������I��������
//	for (auto it : transDirList) {
//		if (it->sourceName == _sourceName &&
//			it->dirName == _dirName)
//			return false;
//	}
//
//	// �V����TransDirection�𐶐�
//	TransDirection* newDir = new TransDirection(_sourceName, _dirName);
//	transDirList.emplace_back(newDir);
//
//	return true;
//}
//
//bool Animator2D::AddTransDirInfo(std::string _sourceName, std::string _dirName, std::string _boolName, bool _enable)
//{
//	// �Ή�����TransDirection�𒊏o
//	TransDirection* dir = nullptr;
//	for (auto it : transDirList) {
//		if (it->sourceName == _sourceName &&
//			it->dirName == _dirName) {
//			dir = it;
//			break;
//		}
//	}
//	if (dir == nullptr) return false;	// ���o���s�ŏI��
//
//	// ���Ɏg���Ă���bool������������A�ǉ������I��
//	for (auto it : dir->info.transBool) {
//		if (it->boolName == _boolName)
//			return false;
//	}
//
//	// �V�����J�ڏ�����ǉ�
//	for (auto it : boolList) {	// bool���X�g����Ή�����bool��ǉ�
//		if (it->boolName == _boolName) {
//			dir->info.transBool.emplace_back(it);
//			break;
//		}
//	}
//	dir->info.transState.emplace_back(_enable);
//
//	return true;
//}
//
//void Animator2D::TransAnimation()
//{
//	if (controller-> != nextAnimName) {
//		for (auto anim : animList) {
//			if (anim->name == nextAnimName) {
//				currentAnim = anim;
//				drawNum = currentAnim->start;
//				currentAnimName = nextAnimName;
//				animCount = 0.0f;
//				imageRenderer->SetImageNumber(drawNum);
//			}
//		}
//	}
//}
//
//bool Animator2D::IsTranslate(TransDirection*& _dir)
//{
//	// ���݂̃A�j���[�V�����̖��O�ƈ�v����SourceName��TransDir��S�Ē��o
//	std::list<TransDirection*> checkDir;
//	for (auto it : transDirList) {
//		if (it->sourceName == currentAnimName) {
//			checkDir.emplace_back(it);
//		}
//	}
//	if (checkDir.size() == 0) return false;	// ������Ȃ���ΏI��
//
//	// ���o����TransDir�̒�����A�J�ڏ����𖞂����Ă�����̂��P���o
//	TransDirection* transDir = nullptr;
//	for (auto it : checkDir) {
//		if (it->IsTranslate()) {
//			transDir = it;
//			break;
//		}
//	}
//	if (transDir == nullptr) return false;	// ������Ȃ���ΏI��
//
//	// ���o����TransDir����
//	_dir = transDir;
//	return true;
//}
//
//bool Animator2D::TransDirInfo::IsTranslate()
//{
//	int size = static_cast<int>(transBool.size());
//	for (int i = 0; i < size; ++i) {
//		// �J�ڏ����ƈ�v���Ă��Ȃ�bool������ΑJ�ڂ��Ȃ�
//		if (transBool.at(i)->enable != transState.at(i))
//			return false;
//	}
//	return true;
//}
//
//bool Animator2D::TransDirection::IsTranslate()
//{
//	return info.IsTranslate();
//}
