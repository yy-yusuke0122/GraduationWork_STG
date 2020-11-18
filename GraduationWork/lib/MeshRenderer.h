#pragma once

#include <unordered_map>

#include <vector>

#include <string>

#include "Transform.h"

#include "Renderer.h"

#include "Material.h"

#include "Texture.h"

#include "Bone.h"

struct MeshRendererInfo;

class MeshRenderer :public Renderer
{
public:
	MeshRenderer();

	~MeshRenderer();

	void Draw()override;

public:
	/// <summary>
	/// �p�X���烂�f���ǂݍ���
	/// </summary>
	/// <param name="_path">�p�X</param>
	/// <returns>true�F�ǂݍ��ݐ����Afalse�F���s</returns>
	bool Load(const std::string& _path);

	/// <summary>
	/// �ǂݍ��񂾃f�[�^��j��
	/// </summary>
	void Release();

	/// <summary>
	/// �ǂݍ���ł���t�@�C���̃p�X���擾
	/// </summary>
	/// <returns></returns>
	std::string GetPath()const { return path; }

	/// <summary>
	/// �ǂݍ��񂾃��f���̃n���h�����擾
	/// </summary>
	/// <returns>-1�ȊO�F�ǂݍ���ł���A-1�F�ǂݍ���ł��Ȃ�</returns>
	int GetHandle()const;

	/// <summary>
	/// ���f�����g�p���Ă���}�e���A���擾
	/// </summary>
	/// <param name="_count">�}�e���A���ԍ�</param>
	/// <returns>null�ȊO�F�g�p�}�e���A���Anull�F�}�e���A�������݂��Ȃ�</returns>
	Material* GetMaterial(unsigned _count);

	/// <summary>
	/// ���f�����g�p���Ă���e�N�X�`���擾
	/// </summary>
	/// <param name="_count">�e�N�X�`���ԍ�</param>
	/// <returns>null�ȊO�F�g�p�e�N�X�`���Anull�F�e�N�X�`�������݂��Ȃ�</returns>
	Texture* GetTexture(unsigned _count);

	/// <summary>
	/// ���f�����g�p���Ă���{�[���擾
	/// </summary>
	/// <param name="_count">�{�[���ԍ�</param>
	/// <returns>null�ȊO�F�g�p�{�[���Anull�F�{�[�������݂��Ȃ�</returns>
	Bone* GetBone(unsigned _count);

	/// <summary>
	/// ���f�����g�p���Ă���}�e���A���擾
	/// </summary>
	/// <param name="_count">�}�e���A����</param>
	/// <returns>null�ȊO�F�g�p�}�e���A���Anull�F�}�e���A�������݂��Ȃ�</returns>
	Material* GetMaterial(const std::string& _name);

	/// <summary>
	/// ���f�����g�p���Ă���e�N�X�`���擾
	/// </summary>
	/// <param name="_count">�e�N�X�`����</param>
	/// <returns>null�ȊO�F�g�p�e�N�X�`���Anull�F�e�N�X�`�������݂��Ȃ�</returns>
	Texture* GetTexture(const std::string& _name);

	/// <summary>
	/// ���f�����g�p���Ă���{�[���擾
	/// </summary>
	/// <param name="_count">�{�[����</param>
	/// <returns>null�ȊO�F�g�p�{�[���Anull�F�{�[�������݂��Ȃ�</returns>
	Bone* GetBone(const std::string& _name);

	/// <summary>
	/// ���f�����g�p���Ă���}�e���A�����擾
	/// </summary>
	/// <returns>�}�e���A����</returns>
	unsigned GetMaterialCount()const { return static_cast<unsigned>(materials.size()); }

	/// <summary>
	/// ���f�����g�p���Ă���e�N�X�`�����擾
	/// </summary>
	/// <returns>�e�N�X�`����</returns>
	unsigned GetTextureCount()const{ return static_cast<unsigned>(textures.size()); }

	/// <summary>
	/// ���f�����g�p���Ă���{�[�����擾
	/// </summary>
	/// <returns>�{�[����</returns>
	unsigned GetBoneCount()const{ return static_cast<unsigned>(bones.size()); }

private:
	void Initialize()override;

	void InitializeParam();

	int CheckAsyncLoading() override;

	void DestroyParam()override;

public:
	Transform renderTransform;

	float alpha;//�����x�i0�`1�E0�œ����A1�ŕs�����j

	COLOR_F
		diffuse, //�g�U�X�P�[���i0�`1�j
		specular, //���ʃX�P�[���i0�`1�j
		ambient, //���X�P�[���i0�`1�j
		emissive;//���Ȕ����F�X�P�[���i0�`1�j

	bool isLighting;//���C�e�B���O���s����

	bool isShadow;//�e��t���邩

private:
	MeshRendererInfo* info;

	std::string path;

	std::vector<Material> materials;

	std::vector<Texture> textures;

	std::vector<Bone> bones;

	static std::unordered_map<std::string, MeshRendererInfo> meshInfo;

};
