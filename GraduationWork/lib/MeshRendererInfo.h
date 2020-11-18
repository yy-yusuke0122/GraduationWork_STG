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

		int diffuseTex;//ディフューズマップ番号
		int specularTex;//スペキュラマップ番号
		int normalTex;//法線マップ番号

		COLOR_F
			diffuse, //拡散（0～1）
			specular, //鏡面（0～1）
			ambient, //環境（0～1）
			emissive;//自己発光色（0～1）

		float specularPow;

		float toonSize;//トゥーンレンダリングの輪郭線の太さ
	
		COLOR_F toonColor;

		int blendMode;

		int blendParam;
	};

	struct TextureInfo
	{
		std::string name;
		
		int handle;

		int modeU, modeV;//UVアドレス指定モード

		int sample;
	};

	struct BoneInfo
	{		
		std::string name;

		int parent;//いない場合、-1

		std::vector<int> children;

		bool isDisp;

		bool isSemiTrans;

		std::vector<int> meshes;//ボーンに含まれるメッシュ
	};

	struct MeshInfo
	{
		bool isDisp;

		bool isSemiTrans;//半透明

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
