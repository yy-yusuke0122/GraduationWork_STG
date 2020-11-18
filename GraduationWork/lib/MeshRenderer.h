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
	/// パスからモデル読み込み
	/// </summary>
	/// <param name="_path">パス</param>
	/// <returns>true：読み込み成功、false：失敗</returns>
	bool Load(const std::string& _path);

	/// <summary>
	/// 読み込んだデータを破棄
	/// </summary>
	void Release();

	/// <summary>
	/// 読み込んでいるファイルのパスを取得
	/// </summary>
	/// <returns></returns>
	std::string GetPath()const { return path; }

	/// <summary>
	/// 読み込んだモデルのハンドルを取得
	/// </summary>
	/// <returns>-1以外：読み込んでいる、-1：読み込んでいない</returns>
	int GetHandle()const;

	/// <summary>
	/// モデルが使用しているマテリアル取得
	/// </summary>
	/// <param name="_count">マテリアル番号</param>
	/// <returns>null以外：使用マテリアル、null：マテリアルが存在しない</returns>
	Material* GetMaterial(unsigned _count);

	/// <summary>
	/// モデルが使用しているテクスチャ取得
	/// </summary>
	/// <param name="_count">テクスチャ番号</param>
	/// <returns>null以外：使用テクスチャ、null：テクスチャが存在しない</returns>
	Texture* GetTexture(unsigned _count);

	/// <summary>
	/// モデルが使用しているボーン取得
	/// </summary>
	/// <param name="_count">ボーン番号</param>
	/// <returns>null以外：使用ボーン、null：ボーンが存在しない</returns>
	Bone* GetBone(unsigned _count);

	/// <summary>
	/// モデルが使用しているマテリアル取得
	/// </summary>
	/// <param name="_count">マテリアル名</param>
	/// <returns>null以外：使用マテリアル、null：マテリアルが存在しない</returns>
	Material* GetMaterial(const std::string& _name);

	/// <summary>
	/// モデルが使用しているテクスチャ取得
	/// </summary>
	/// <param name="_count">テクスチャ名</param>
	/// <returns>null以外：使用テクスチャ、null：テクスチャが存在しない</returns>
	Texture* GetTexture(const std::string& _name);

	/// <summary>
	/// モデルが使用しているボーン取得
	/// </summary>
	/// <param name="_count">ボーン名</param>
	/// <returns>null以外：使用ボーン、null：ボーンが存在しない</returns>
	Bone* GetBone(const std::string& _name);

	/// <summary>
	/// モデルが使用しているマテリアル数取得
	/// </summary>
	/// <returns>マテリアル数</returns>
	unsigned GetMaterialCount()const { return static_cast<unsigned>(materials.size()); }

	/// <summary>
	/// モデルが使用しているテクスチャ数取得
	/// </summary>
	/// <returns>テクスチャ数</returns>
	unsigned GetTextureCount()const{ return static_cast<unsigned>(textures.size()); }

	/// <summary>
	/// モデルが使用しているボーン数取得
	/// </summary>
	/// <returns>ボーン数</returns>
	unsigned GetBoneCount()const{ return static_cast<unsigned>(bones.size()); }

private:
	void Initialize()override;

	void InitializeParam();

	int CheckAsyncLoading() override;

	void DestroyParam()override;

public:
	Transform renderTransform;

	float alpha;//透明度（0～1・0で透明、1で不透明）

	COLOR_F
		diffuse, //拡散スケール（0～1）
		specular, //鏡面スケール（0～1）
		ambient, //環境スケール（0～1）
		emissive;//自己発光色スケール（0～1）

	bool isLighting;//ライティングを行うか

	bool isShadow;//影を付けるか

private:
	MeshRendererInfo* info;

	std::string path;

	std::vector<Material> materials;

	std::vector<Texture> textures;

	std::vector<Bone> bones;

	static std::unordered_map<std::string, MeshRendererInfo> meshInfo;

};
