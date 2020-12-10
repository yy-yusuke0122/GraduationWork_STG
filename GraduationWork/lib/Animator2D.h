#pragma once
#include "Component.h"
#include "Anim2D.h"
#include <vector>

class ImageRenderer;
class Anim2D;
class StateManager;

class Animator2D : public Component {
public:
	Animator2D();
	virtual ~Animator2D();
	void Start() final override;
	void Update() final override;

	/*/// <summary>
	/// �V�K�A�j���[�V������ǉ�����
	/// </summary>
	/// <param name="_start">�J�n�v�f�ԍ�</param>
	/// <param name="_end">�I���v�f�ԍ�</param>
	/// <param name="_animName">�A�j���[�V������</param>
	/// <param name="_animSpeed">�A�j���[�V�����X�s�[�h</param>
	/// <param name="_isLoop">���[�v���邩(true : ���[�v����)</param>
	/// <returns>true:�ǉ�����, false:���ɒǉ�����Ă���</returns>
	bool AddAnim(unsigned int _start, unsigned int _end, std::string _animName, float _animSpeed = 1.0f, bool _isLoop = true);

	/// <summary>
	/// ���߂ɍĐ������A�j���[�V������ݒ肷��
	/// </summary>
	/// <param name="_animName">�A�j���[�V������</param>
	/// <returns>true:����, false:�A�j���[�V������������Ȃ�</returns>
	bool SetStartAnim(std::string _animName);

	/// <summary>
	/// �A�j���[�V�������擾����
	/// </summary>
	/// <param name="_animName">�A�j���[�V������</param>
	/// <returns>nullptr:�擾���s</returns>
	Anim2D* GetAnim(std::string _animName);

	/// <summary>
	/// ���݂̃A�j���[�V�������擾����
	/// </summary>
	/// <returns>nullptr:�擾���s</returns>
	Anim2D* GetCurrentAnim();

	/// <summary>
	/// �`��ԍ����擾����
	/// </summary>
	/// <returns>�`�悷��v�f�ԍ�</returns>
	int GetDrawNum() const;

	/// <summary>
	/// �`��ԍ���ݒ肷��
	/// </summary>
	/// <param name="_num">�`��ԍ�</param>
	/// <returns>true:����, false:�͈͊O�̕`��ԍ����w�肵�Ă��邽�߁A�G���[</returns>
	bool SetDrawNum(unsigned int _num);

	/// <summary>
	/// �w�肵���A�j���[�V�����pbool�^�̏�Ԃ��擾
	/// </summary>
	/// <param name="_boolName">�A�j���[�V����bool�̖��O</param>
	/// <returns>�A�j���[�V����bool�̒l</returns>
	bool GetBool(std::string _boolName);

	/// <summary>
	/// �w�肵���A�j���[�V�����pbool�^�̏�Ԃ�ύX
	/// </summary>
	/// <param name="_boolName">�A�j���[�V����bool�̖��O</param>
	/// <param name="_bool">�ݒ肵�����l</param>
	void SetBool(std::string _boolName, bool _bool);

	/// <summary>
	/// �A�j���[�V�����pbool�^��V�ɒǉ�����
	/// </summary>
	/// <param name="_boolName">�ݒ肵�������O</param>
	/// <returns>true:����, false:���ɑ��݂��Ă���</returns>
	bool CreateBool(std::string _boolName);

	/// <summary>
	/// �A�j���[�V�����J�ڂ̗����V���ɒǉ�����
	/// </summary>
	/// <param name="_sourceName">�J�ڑO�̃A�j���[�V������</param>
	/// <param name="_dirName">�J�ڐ�̃A�j���[�V������</param>
	/// <returns>true:����, false:���ɑ��݂��Ă���</returns>
	bool CreateTransDirection(std::string _sourceName, std::string _dirName);

	/// <summary>
	/// �A�j���[�V�����J�ڂ̗����\�����ɁA�J�ڏ�����ǉ�����
	/// </summary>
	/// <param name="_sourceName">�J�ڑO�̃A�j���[�V������</param>
	/// <param name="_dirName">�J�ڐ�̃A�j���[�V������</param>
	/// <param name="_boolName">�A�j���[�V����bool�̖��O</param>
	/// <param name="_enable">�ݒ肵�����l</param>
	/// <returns>true:����, false:���s</returns>
	bool AddTransDirInfo(std::string _sourceName, std::string _dirName, std::string _boolName, bool _enable);

private:
	StateController* controller;
	ImageRenderer* imageRenderer;
	std::list<Anim2D*> animList;
	Anim2D* currentAnim;
	std::string currentAnimName;
	std::string nextAnimName;
	float animCount;
	unsigned int drawNum;

private:
	/// <summary>
	/// �A�j���[�V�����؂�ւ���
	/// </summary>
	void TransAnimation();*/
};