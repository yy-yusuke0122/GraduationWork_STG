#pragma once

#include <string>

struct MeshRendererInfo;

class Material;

class Texture
{
	friend class MeshRenderer;//���x����̂���

public:
	enum ADDRESS_MODE
	{
		DEFAULT,
		WRAP,
		MIRROR,
		CLAMP,
		BORDER
	};

	enum SAMPLE
	{
		NEAREST,
		BILINEAR,
		ANISOTROPIC
	};

public:
	Texture()
	{
	}

	~Texture()
	{
	}

	void Set();

public:
	/// <summary>
	/// �e�N�X�`�����擾
	/// </summary>
	/// <returns>�e�N�X�`����</returns>
	std::string GetName()const;

	/// <summary>
	/// ���f�����̃e�N�X�`���ԍ��擾
	/// </summary>
	/// <returns>�e�N�X�`���ԍ�</returns>
	int GetNo()const { return no; }

	/// <summary>
	/// UV�A�h���X���[�h�Z�b�g
	/// ���s���A�p�����[�^�̓Z�b�g����܂���
	/// </summary>
	/// <param name="_u">U�ɃZ�b�g����A�h���X���[�h</param>
	/// <param name="_v">V�ɃZ�b�g����A�h���X���[�h</param>
	/// <returns>�����Ftrue�A���s�Ffalse</returns>
	bool SetMode(int _u, int _v);

	/// <summary>
	/// UV�A�h���X���[�h�擾
	/// </summary>
	/// <param name="_u">U�A�h���X���[�h�i�[</param>
	/// <param name="_v">V�A�h���X���[�h�i�[</param>
	void GetMode(int& _u, int& _v);

	/// <summary>
	/// �T���v���Z�b�g
	/// </summary>
	/// <param name="_sample">�Z�b�g����T���v���l</param>
	/// <returns>�����Ftrue�A���s�Ffalse</returns>
	bool SetSample(int _sample);

	/// <summary>
	/// �T���v���擾
	/// </summary>
	/// <returns>�T���v��</returns>
	int GetSample()const { return sample; }

private:
	int no;//�ԍ�

	int modeU, modeV;//UV�A�h���X�w�胂�[�h

	int sample;

	MeshRendererInfo* info;

public:
	int handle;//�摜�n���h���i�f�t�H���g��-1�j

};
