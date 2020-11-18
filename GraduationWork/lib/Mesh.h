#pragma once

#include "dxlib/DxLib.h"

struct MeshRendererInfo;

class MeshRenderer;

class Material;

class Mesh
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
	Mesh();

	~Mesh()
	{
	}

	void Set();

public:
	/// <summary>
	/// ���f�����̃��b�V���ԍ��擾
	/// </summary>
	/// <returns>���b�V���ԍ�</returns>
	int GetNo()const { return no; }

	/// <summary>
	/// �������v�f���܂܂�Ă��邩
	/// </summary>
	/// <returns>true�F�܂܂�Ă���Afalse�F�܂܂�Ă��Ȃ�</returns>
	bool IsSemiTrans()const;

	/// <summary>
	/// ���b�V���Ɏg���Ă���}�e���A���擾
	/// </summary>
	/// <returns>null�ȊO�F�g�p�}�e���A���Anull�F�g�p���Ă��Ȃ�</returns>
	Material* GetMaterial()const;

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

public:
	COLOR_F
		diffuse, //�g�U�X�P�[���i0�`1�j
		specular, //���ʃX�P�[���i0�`1�j
		ambient, //���X�P�[���i0�`1�j
		emissive;//���Ȕ����F�X�P�[���i0�`1�j

	bool isDisp;//�\��

	float alpha;//0�`1

	int blendParam;//0�`255

private:
	MeshRendererInfo* info;

	MeshRenderer* renderer;

	int no;//�ԍ�

	int blendMode;

};
