#pragma once

#include "typedef.h"
#include "Renderer.h"
#include "Image.h"
#include <string>
#include <vector>

class ImageRenderer : public Renderer {
	friend Image;
public:
	ImageRenderer();
	~ImageRenderer();
	void Draw();

	/// <summary>
	/// �摜��ǂݍ���
	/// </summary>
	/// <param name="_filePass">�Ǎ��݂����摜�t�@�C���̃p�X</param>
	/// <returns>�ǂݍ��ݐ�����true, �t�@�C����������Ȃ������ɓ������̂�ǂݍ���ł�����false</returns>
	bool SetImage(const std::string& _filePass);

	/// <summary>
	/// �摜�𕪊��ǂݍ���
	/// </summary>
	/// <param name="_filePass">�Ǎ��݂����摜�t�@�C���̃p�X</param>
	/// <param name="_xdiv">��������</param>
	/// <param name="_ydiv">�c������</param>
	/// <param name="_allnum">�S�̕������A0��_xdiv*_ydiv</param>
	/// <returns>true�F�ǂݍ��ݐ����Afalse�F���s</returns>
	bool SetImageDiv(const std::string& _filePass, unsigned _xdiv, unsigned _ydiv, unsigned _allnum = 0u);

	/// <summary>
	/// �摜�n���h���擾
	/// </summary>
	/// <returns>�摜�n���h��</returns>
	std::vector<int> GetHandle()const { return image.imageInfo->handles; }

	/// <summary>
	/// �`��ԍ����Z�b�g
	/// </summary>
	/// <returns>true�F�����Afalse�F�͈͊O</returns>
	bool SetImageNumber(unsigned _num);

	/// <summary>
	/// �`��ԍ��擾
	/// </summary>
	/// <returns>�`��ԍ�</returns>
	unsigned GetDrawNumber()const { return drawNum; }

	/// <summary>
	/// �`��ő�ԍ��擾
	/// </summary>
	/// <returns>�`��ő�ԍ�</returns>
	unsigned GetDrawMaxNumber()const;

	/// <summary>
	/// �ǂݍ���ł���t�@�C���̃p�X���擾
	/// </summary>
	/// <returns>�t�@�C���p�X</returns>
	std::string GetPath()const { return image.path; }

	/// <summary>
	/// �摜X�T�C�Y���擾
	/// </summary>
	/// <returns>�ǂݍ��ݎ��F�摜�T�C�Y�A�ǂݍ���ł��Ȃ��F-1</returns>
	int GetSizeX()const;

	/// <summary>
	/// �摜Y�T�C�Y���擾
	/// </summary>
	/// <returns>�ǂݍ��ݎ��F�摜�T�C�Y�A�ǂݍ���ł��Ȃ��F-1</returns>
	int GetSizeY()const;

	/// <summary>
	/// �ǂݍ��񂾃f�[�^��j��
	/// </summary>
	void Release() { image.Destroy(); drawNum = 0u; }

private:
	void Initialize();

	int CheckAsyncLoading() override;

	void DestroyParam()override;

public:
	VECTOR2 position;
	float rotation;
	VECTOR2 scale;
	float alpha;
	int transFlag;
	bool turnXFlag;
	bool turnYFlag;
	int order;

private:
	Image image;

	unsigned drawNum;
};