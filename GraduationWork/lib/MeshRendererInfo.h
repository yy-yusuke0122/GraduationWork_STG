#pragma once

#include <vector>
#include <list>
#include <string>
#include "dxlib/DxLib.h"

class MeshRenderer;

struct MeshRendererInfo
{
	struct MaterialInfo
	{
		std::string name;

		int diffuseTex;//�f�B�t���[�Y�}�b�v�ԍ�
		int specularTex;//�X�y�L�����}�b�v�ԍ�
		int normalTex;//�@���}�b�v�ԍ�

		COLOR_F
			diffuse, //�g�U�i0�`1�j
			specular, //���ʁi0�`1�j
			ambient, //���i0�`1�j
			emissive;//���Ȕ����F�i0�`1�j

		float specularPow;

		float toonSize;//�g�D�[�������_�����O�̗֊s���̑���
	
		COLOR_F toonColor;

		int blendMode;

		int blendParam;
	};

	struct TextureInfo
	{
		std::string name;
		
		int handle;

		int modeU, modeV;//UV�A�h���X�w�胂�[�h

		int sample;
	};

	struct BoneInfo
	{		
		std::string name;

		int parent;//���Ȃ��ꍇ�A-1

		std::vector<int> children;

		bool isDisp;

		bool isSemiTrans;

		std::vector<int> meshes;//�{�[���Ɋ܂܂�郁�b�V��
	};

	struct MeshInfo
	{
		bool isDisp;

		bool isSemiTrans;//������

		int blendMode;

		int blendParam;

		int materialNo;
	};

	MeshRendererInfo() :count(1), isAsync(false) {}
	int handle;
	int count;
	
	std::vector<MaterialInfo> materials;
	std::vector<TextureInfo> textures;
	std::vector<BoneInfo> bones;
	std::vector<MeshInfo> meshes;

	std::list<MeshRenderer*> asyncList;

	bool isAsync;
};
