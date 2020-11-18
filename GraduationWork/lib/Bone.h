#pragma once

#include <string>

#include <vector>

#include "dxlib/DxLib.h"

#include "Mesh.h"

#include "typedef.h"

struct MeshRendererInfo;

class MeshRenderer;

class Bone
{
	friend MeshRenderer;//���x����̂���

public:
	Bone();

	~Bone()
	{
	}

	void Set();

public:
	/// <summary>
	/// �{�[�����擾
	/// </summary>
	/// <returns>�{�[����</returns>
	std::string GetName()const;

	/// <summary>
	/// ���f�����̃{�[���ԍ��擾
	/// </summary>
	/// <returns>�{�[���ԍ�</returns>
	int GetNo()const { return no; }

	/// <summary>
	/// �e�{�[���擾
	/// </summary>
	/// <returns>null�ȊO�F�e�{�[���Anull�F�e�{�[�����݂͂��Ȃ�</returns>
	Bone* GetParent();

	/// <summary>
	/// �q�{�[���̐��擾
	/// </summary>
	/// <returns>�q�{�[���̐�</returns>
	unsigned GetChildCount()const;

	/// <summary>
	/// �q�{�[���擾
	/// </summary>
	/// <param name="_count">�擾����q�ԍ�</param>
	/// <returns>null�ȊO�F�q�{�[���Anull�F�q�{�[�����݂͂��Ȃ�</returns>
	Bone* GetChild(unsigned _count);

	/// <summary>
	/// �q�{�[���擾
	/// </summary>
	/// <param name="_name">�擾����q�̖��O</param>
	/// <returns>null�ȊO�F�q�{�[���Anull�F�q�{�[�����݂͂��Ȃ�</returns>
	Bone* GetChild(const std::string& _name);

	/// <summary>
	/// �������v�f���܂܂�Ă��邩
	/// </summary>
	/// <returns>true�F�܂܂�Ă���Afalse�F�܂܂�Ă��Ȃ�</returns>
	bool IsSemiTrans()const;

	/// <summary>
	/// �{�[���̃��[���h���W�擾
	/// </summary>
	/// <returns>���[���h���W</returns>
	VECTOR3 GetWorldPosition()const;

	/// <summary>
	/// �{�[���̃��[���h�ϊ��s��擾
	/// </summary>
	/// <returns>���[���h�ϊ��s��</returns>
	MATRIX GetWorldMatrix()const;

	/// <summary>
	/// �{�[���Ɋ܂܂�郁�b�V�������擾
	/// </summary>
	/// <returns>���b�V�������擾</returns>
	unsigned GetMeshCount()const;

	/// <summary>
	/// �{�[���Ɋ܂܂�郁�b�V���擾
	/// </summary>
	/// <param name="_count">�{�[�����̃��b�V���ԍ�</param>
	/// <returns>null�ȊO�F���b�V���Anull�F���b�V�������݂��Ȃ�</returns>
	Mesh* GetMesh(unsigned _count);

private:
	int no;//�ԍ�

	MeshRendererInfo* info;

	std::vector<Mesh> meshes;

	MeshRenderer* renderer;

public:
	bool isDisp;//�\��

	COLOR_F
		diffuse, //�g�U�X�P�[���i0�`1�j
		specular, //���ʃX�P�[���i0�`1�j
		ambient, //���X�P�[���i0�`1�j
		emissive;//���Ȕ����F�X�P�[���i0�`1�j

	float alpha;//0�`1

};
