#pragma once

#include "dxlib/DxLib.h"
#include <string>

struct MeshRendererInfo;

class Texture;

class MeshRenderer;

class Material
{
	friend MeshRenderer;//���x����̂���

public:
	enum BLEND
	{
		NONE,
		ALPHA,
		ADD,
		SUB,
		MUL,
		INVSRC = DX_BLENDMODE_INVSRC
	};

public:
	Material() :isToonDot(false) {}

	~Material() {}

	void Set();

public:
	/// <summary>
	/// �}�e���A�����擾
	/// </summary>
	/// <returns>�}�e���A����</returns>
	std::string GetName()const;

	/// <summary>
	/// ���f�����̃}�e���A���ԍ�
	/// </summary>
	/// <returns>�}�e���A���ԍ�</returns>
	int GetNo()const { return no; }

	/// <summary>
	/// �f�B�t���[�Y�}�b�v�Ƃ��Ďg�p���Ă���e�N�X�`���擾
	/// </summary>
	/// <returns>null�ȊO�F�f�B�t���[�Y�}�b�v�E�e�N�X�`���Anull�F�f�B�t���[�Y�}�b�v���g�p���Ă��Ȃ�</returns>
	Texture* GetDiffuseMap()const;

	/// <summary>
	/// �X�y�L�����}�b�v�Ƃ��Ďg�p���Ă���e�N�X�`���擾
	/// </summary>
	/// <returns>null�ȊO�F�X�y�L�����}�b�v�E�e�N�X�`���Anull�F�X�y�L�����}�b�v���g�p���Ă��Ȃ�</returns>
	Texture* GetSpecularMap()const;

	/// <summary>
	/// �m�[�}���}�b�v�Ƃ��Ďg�p���Ă���e�N�X�`���擾
	/// </summary>
	/// <returns>null�ȊO�F�m�[�}���}�b�v�E�e�N�X�`���Anull�F�m�[�}���}�b�v���g�p���Ă��Ȃ�</returns>
	Texture* GetNormalMap()const;

	/// <summary>
	/// �u�����h���[�h�擾
	/// </summary>
	/// <returns>�u�����h���[�h</returns>
	int GetBlendMode()const { return blendMode; }

	/// <summary>
	/// �u�����h���[�h�Z�b�g
	/// </summary>
	/// <param name="_mode">�Z�b�g����u�����h���[�h</param>
	/// <returns>true�F�����Afalse�F���s</returns>
	bool SetBlendMode(int _mode);

private:
	int no;//�ԍ�

	MeshRenderer* renderer;

	MeshRendererInfo* info;

	int blendMode;

public:
	COLOR_F
		diffuse, //�g�U�X�P�[���i0�`1�j
		specular, //���ʃX�P�[���i0�`1�j
		ambient, //���X�P�[���i0�`1�j
		emissive;//���Ȕ����F�X�P�[���i0�`1�j

	float specularPow;

	float toonSize;//�g�D�[���֊s������

	bool isToonDot;//�g�D�[���֊s�����h�b�g�Ŏw�肷��

	COLOR_F toonColor;//�g�D�[���֊s���F

	int blendParam;//0�`255

};
