#pragma once
#include "StateMachine.h"
#include "Component.h"
#include <map>

class ImageRenderer;
class Anim2D;

//class Animator2D : public Component {
//public:
//	Animator2D();
//	virtual ~Animator2D();
//	void Start() final override;
//	void Update() final override;
//
//	/// <summary>
//	/// �V�K�A�j���[�V������ǉ�����
//	/// </summary>
//	/// <param name="_animName">�A�j���[�V������</param>
//	/// <param name="_start">�J�n�v�f�ԍ�(0�ȏ�̒l)</param>
//	/// <param name="_end">�I���v�f�ԍ�(start�ȏ�̒l)</param>
//	/// <param name="_animSpeed">�A�j���[�V�����X�s�[�h(0.0f�ȏ�̒l)</param>
//	/// <param name="_isLoop">���[�v���邩(true : ���[�v����)</param>
//	/// <returns>true:�ǉ�����, false:���ɒǉ�����Ă��邩�A�s���Ȓl��n���Ă���</returns>
//	bool AddAnim(std::string _animName, unsigned int _start, unsigned int _end, float _animSpeed = 1.0f, bool _isLoop = true);
//
//	/// <summary>
//	/// ���߂ɍĐ������A�j���[�V������ݒ肷��
//	/// </summary>
//	/// <param name="_animName">�A�j���[�V������</param>
//	/// <returns>true:����, false:�A�j���[�V������������Ȃ�</returns>
//	bool SetStartAnim(std::string _animName);
//
//	/// <summary>
//	/// �A�j���[�V�������擾����
//	/// </summary>
//	/// <param name="_animName">�A�j���[�V������</param>
//	/// <returns>nullptr:�擾���s</returns>
//	Anim2D* GetAnim(std::string _animName);
//
//	/// <summary>
//	/// ���݂̃A�j���[�V�������擾����
//	/// </summary>
//	/// <returns>nullptr:�擾���s</returns>
//	Anim2D* GetCurrentAnim();
//
//	/// <summary>
//	/// �`��ԍ����擾����
//	/// </summary>
//	/// <returns>�`�悷��v�f�ԍ�</returns>
//	int GetDrawNum() const;
//
//	/// <summary>
//	/// �`��ԍ���ݒ肷��
//	/// </summary>
//	/// <param name="_num">�`��ԍ�</param>
//	/// <returns>true:����, false:�͈͊O�̕`��ԍ����w�肵�Ă��邽�߁A�G���[</returns>
//	bool SetDrawNum(unsigned int _num);
//
//private:
//	StateController* controller;
//	ImageRenderer* imageRenderer;
//	std::list<Anim2D*> animList;
//	Anim2D* currentAnim;
//	std::string currentAnimName;
//	std::string nextAnimName;
//	unsigned int drawNum;
//};

class Animator2D : public Component {
public:
	Animator2D();
	~Animator2D();
	void Start();
	void Update();

	/// <summary>
	/// �X�e�[�^�X�}�V�����Z�b�g����
	/// </summary>
	/// <param name="_stateMachine">�ݒ肷��X�e�[�g�}�V�[��</param>
	/// <returns>true:����, false:���ɐݒ肵���X�e�[�g�}�V�[�������݂���</returns>
	bool SetStateMachine(StateMachine* _stateMachine);

	/// <summary>
	/// ���݂̃X�e�[�^�X���擾����
	/// </summary>
	/// <returns></returns>
	std::string GetState() const;

	/// <summary>
	/// �J�ڏ����̏�Ԃ��擾����
	/// </summary>
	/// <param name="_boolName">�擾�������J�ڏ�����</param>
	/// <returns>�J�ڏ����̏�Ԃ��A���݂��Ȃ��J�ڏ������擾���悤�Ƃ����ꍇfalse</returns>
	bool GetBool(const std::string& _boolName);

	/// <summary>
	/// �w�肵���J�ڏ����ɒl��ݒ肷��
	/// </summary>
	/// <param name="_boolName">�ݒ肵�����J�ڏ�����</param>
	/// <param name="_bool">�ݒ肵�����l</param>
	/// <returns>true:����, false:���݂��Ȃ��J�ڏ���</returns>
	bool SetBool(const std::string& _boolName, bool _bool);

	/// <summary>
	/// �X�e�[�^�X�ɃA�j���[�V������ݒ肷��
	/// </summary>
	/// <param name="_stateName">�ݒ肵�����A�j���[�V����</param>
	/// <param name="_filePass">�A�j���[�V�����ɂ��悤����摜�̃t�@�C���p�X</param>
	/// <param name="_xdiv">�������̕�����</param>
	/// <param name="_ydiv">�c�����̕�����</param>
	/// <param name="_allnum">�g�p����v�f��</param>
	/// <param name="_playSpeed">1�b������̍Đ����x</param>
	/// <param name="_start">�J�n�v�f�ԍ�</param>
	/// <param name="_end">�I���v�f�ԍ�</param>
	/// <param name="_isLoop">���[�v���邩�ǂ���</param>
	/// <returns>�ݒ��̃A�j���[�V�����̃|�C���^�[, nullptr:�s���Ȓl���A���ɐݒ肳��Ă���</returns>
	Anim2D* SetAnim(const std::string& _stateName, const std::string& _filePass, unsigned int _xdiv, unsigned int _ydiv, unsigned int _allnum, float _playSpeed = 1.0f, unsigned int _start = 0, unsigned int _end = 0, bool _isLoop = true);

	/// <summary>
	/// �X�e�[�^�X�ɐݒ肳��Ă���A�j���[�V�������擾����
	/// </summary>
	/// <param name="_stateName">�X�e�[�^�X��</param>
	/// <returns>nullptr:�擾���s</returns>
	Anim2D* GetAnim(const std::string& _stateName);

	/// <summary>
	/// ���݂̃X�e�[�^�X�̃A�j���[�V�������擾����
	/// </summary>
	/// <returns>nullptr:���ݍĐ�����Ă���A�j���[�V���������݂��Ȃ�</returns>
	Anim2D* GetCurrentAnim();

private:
	/// <summary>
	/// �Ή������A�j���[�V�����̃A�h���X���擾����
	/// </summary>
	/// <param name="_name">�X�e�[�^�X��</param>
	/// <returns>nullptr:�Ή������X�e�[�^�X��������Ȃ�</returns>
	Anim2D** FindStateAnim(const std::string& _name);

	/// <summary>
	/// ���݂̃X�e�[�^�X�ɍ��킹���A�j���[�V������L���ɂ���
	/// </summary>
	void ChangeStateAnim();

private:
	ImageRenderer* renderer;
	StateMachine* state;
	Anim2D* currentAnim;
	std::string currentState;
	std::map<std::string, Anim2D*> animations;
};
