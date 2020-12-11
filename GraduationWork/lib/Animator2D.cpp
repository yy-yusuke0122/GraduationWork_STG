//#include "Animator2D.h"
//#include "ImageRenderer.h"
//#include "Time.h"
//#include "Function.h"
//#include "StateController.h"
//
//Animator2D::Animator2D() :
//	controller(nullptr), imageRenderer(nullptr), currentAnim(nullptr), currentAnimName(""), nextAnimName(""), animCount(0.0f), drawNum(0)
//{
//	animList.clear();
//}
//
//Animator2D::Animator2D()
//{
//}
//
//Animator2D::~Animator2D()
//{
//}
//
//void Animator2D::Start()
//{
//}
//
//void Animator2D::Update()
//{
//	if (controller == nullptr)
//		return;
//
//	if (imageRenderer == nullptr) {
//		imageRenderer = GetComponent<ImageRenderer>();
//		if (imageRenderer == nullptr)
//			return;
//	}
//
//	// �A�j���[�V�����؂�ւ�
//	TransAnimation();
//
//	// �Đ����̃A�j���[�V������������ΏI��
//	if (currentAnim == nullptr)
//		return;
//
//	// �A�j���[�V��������
//	animCount += currentAnim->speed * Time::DeltaTime();
//	if (animCount >= 1.0f) {
//		animCount = 0.0f;
//		if (++drawNum > currentAnim->end) {
//			drawNum = currentAnim->start;
//		}
//		imageRenderer->SetImageNumber(drawNum);
//	}
//}
//
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
