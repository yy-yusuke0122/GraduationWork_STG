#pragma once
#include <vector>
#include <string>

class ImageRenderer;

class Anim2D {
public:
	Anim2D(ImageRenderer* _renderer);
	~Anim2D();

	/// <summary>
	/// �A�j���[�V�����̏�����
	/// </summary>
	void Start();

	/// <summary>
	/// �A�j���[�V�����ԍ��̍X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �C���[�W�����_���[�ɉ摜��ݒ肷��
	/// </summary>
	bool ActiveImage();

	/// <summary>
	/// �g�p�����摜�f�[�^��ݒ肷��
	/// </summary>
	/// <param name="_filePass">�t�@�C���p�X</param>
	/// <param name="_xdiv">�������̕�����</param>
	/// <param name="_ydiv">�c�����̕�����</param>
	/// <param name="_allnum">�g�p����v�f��</param>
	/// <returns>true:����, false:�s���Ȓl</returns>
	bool SetUsedImage(const std::string& _filePass, unsigned int _xdiv, unsigned int _ydiv, unsigned int _allnum = 0U);

	/// <summary>
	/// �Đ��ԍ���ݒ肷��
	/// </summary>
	/// <param name="_start">�J�n�ԍ�</param>
	/// <param name="_end">�I���ԍ�</param>
	/// <returns></returns>
	bool SetPlayNum(unsigned int _start, unsigned int _end);

	/// <summary>
	/// �Đ����x��ݒ肷��(0.0f�ȏ�)
	/// </summary>
	/// <param name="_speed">1�b������̍Đ����x</param>
	/// <returns>true:����, false:�s���Ȓl</returns>
	bool SetPlaySpeed(float _speed);

	/// <summary>
	/// ���݂̗v�f�ԍ���ݒ�
	/// </summary>
	/// <param name="_num">�ݒ肵�����v�f�ԍ�</param>
	/// <returns>true:����, false:start����end�͈̔͊O�̂��߃G���[</returns>
	bool SetCurrentNum(unsigned int _num);

	/// <summary>
	/// �t�Đ�����
	/// </summary>
	void Reverse();

	/// <summary>
	/// �Ō�̃A�j���[�V�������ǂ���
	/// </summary>
	/// <returns>�Ō�̃A�j���[�V�����ԍ��Ȃ�true</returns>
	bool IsEndAnim() const;

	bool loopFlag;

private:
	/// <summary>
	/// �t�Đ����Ă��邩�ǂ���
	/// </summary>
	/// <returns>true:���Ă���, false:���Ă��Ȃ�</returns>
	bool IsPlayBack() const;

private:
	ImageRenderer* renderer;
	std::string filePass;
	unsigned int xdiv, ydiv, allnum;
	int start, end;
	int currentNum;
	float speed;
	float time;
};