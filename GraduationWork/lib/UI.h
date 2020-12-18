#pragma once
#include "GameObject.h"
#include <string>
#include <unordered_map>
#include "typedef.h"

class ImageRenderer;
class UpdateButton;
class BoxCollider2D;

class UI : public GameObject {
public:
	UI();
	virtual ~UI();
	virtual void Start();

private:

};

class Text : public UI {
public:
	Text();
	~Text();

	/// <summary>
	/// �t�H���g�f�[�^�𐶐�����
	/// </summary>
	/// <returns>-1:���s, 0�ȏ�:�t�H���g�f�[�^</returns>
	int SetNewFont(char* FontName, int Size, int Thick, int FontType);

	/// <summary>
	/// �������`��
	/// </summary>
	/// <param name="_position">�`�悷��2�������W</param>
	/// <returns>0:����, -1:�G���[����</returns>
	int Draw(VECTOR2 _position);

	/// <summary>
	/// �g�p���Ă��镶����n���h�����擾
	/// </summary>
	/// <returns>-1:�f�t�H���g�̃t�H���g</returns>
	int GetHandle() const { return handle; }

	/// <summary>
	/// �t�H���g�T�C�Y��ύX����
	/// </summary>
	/// <param name="_size">�t�H���g�T�C�Y</param>
	/// <returns>-1:���s, 0�ȏ�:����</returns>
	int SetFontSize(int _size);

	/// <summary>
	/// �t�H���g�̑�����ύX����
	/// </summary>
	/// <param name="_thick">0�`9, -1�Ńf�t�H���g</param>
	/// <returns>-1:���s, 0�ȏ�:����</returns>
	int SetFontThick(int _thick);

	/// <summary>
	/// �t�H���g�^�C�v��ύX����
	/// </summary>
	/// <param name="_type">
	/// -1�Ńf�t�H���g(DX_FONTTYPE_NORMAL�Ɠ���)
	/// DX_FONTTYPE_NORMAL�@�@�@�@�@		: �m�[�}���t�H���g
	/// DX_FONTTYPE_EDGE�@�@�@�@�@�@�@�@	: �G�b�W���t�H���g
	/// DX_FONTTYPE_ANTIALIASING�@�@�@�@	: �A���`�G�C���A�X�t�H���g
	/// DX_FONTTYPE_ANTIALIASING_4X4�@�@�@	: �A���`�G�C���A�X�t�H���g(4x4�T���v�����O)
	/// DX_FONTTYPE_ANTIALIASING_8X8�@�@�@	: �A���`�G�C���A�X�t�H���g(8x8�T���v�����O)
	/// DX_FONTTYPE_ANTIALIASING_EDGE_4X4�@ : �A���`�G�C���A�X���G�b�W�t���t�H���g(4x4�T���v�����O)
	/// DX_FONTTYPE_ANTIALIASING_EDGE_8X8�@ : �A���`�G�C���A�X���G�b�W�t���t�H���g(8x8�T���v�����O) )
	/// </param>
	/// <returns>-1:���s, 0�ȏ�:����</returns>
	int SetFontType(int _type);

	/// <summary>
	/// �`�悷�镶����̐F��ݒ肷��
	/// </summary>
	/// <param name="_color">������̐F�������J���[�R�[�h</param>
	void SetColor(unsigned int _color);

	std::string text;

private:
	int handle;
	char* fontName;
	int size;
	int thick;
	int fontType;
	unsigned int color;
};

class Button : public UI {
public:
	Button();
	~Button();
	void Start();

	Text* textObj;

private:
	ImageRenderer* image;
	UpdateButton* updater;
};