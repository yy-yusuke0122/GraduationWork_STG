#pragma once

#include "dxlib/DxLib.h"
#include <string>

struct MeshRendererInfo;

class Texture;

class MeshRenderer;

class Material
{
	friend MeshRenderer;//速度向上のため

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
	/// マテリアル名取得
	/// </summary>
	/// <returns>マテリアル名</returns>
	std::string GetName()const;

	/// <summary>
	/// モデル内のマテリアル番号
	/// </summary>
	/// <returns>マテリアル番号</returns>
	int GetNo()const { return no; }

	/// <summary>
	/// ディフューズマップとして使用しているテクスチャ取得
	/// </summary>
	/// <returns>null以外：ディフューズマップ・テクスチャ、null：ディフューズマップを使用していない</returns>
	Texture* GetDiffuseMap()const;

	/// <summary>
	/// スペキュラマップとして使用しているテクスチャ取得
	/// </summary>
	/// <returns>null以外：スペキュラマップ・テクスチャ、null：スペキュラマップを使用していない</returns>
	Texture* GetSpecularMap()const;

	/// <summary>
	/// ノーマルマップとして使用しているテクスチャ取得
	/// </summary>
	/// <returns>null以外：ノーマルマップ・テクスチャ、null：ノーマルマップを使用していない</returns>
	Texture* GetNormalMap()const;

	/// <summary>
	/// ブレンドモード取得
	/// </summary>
	/// <returns>ブレンドモード</returns>
	int GetBlendMode()const { return blendMode; }

	/// <summary>
	/// ブレンドモードセット
	/// </summary>
	/// <param name="_mode">セットするブレンドモード</param>
	/// <returns>true：成功、false：失敗</returns>
	bool SetBlendMode(int _mode);

private:
	int no;//番号

	MeshRenderer* renderer;

	MeshRendererInfo* info;

	int blendMode;

public:
	COLOR_F
		diffuse, //拡散スケール（0～1）
		specular, //鏡面スケール（0～1）
		ambient, //環境スケール（0～1）
		emissive;//自己発光色スケール（0～1）

	float specularPow;

	float toonSize;//トゥーン輪郭線太さ

	bool isToonDot;//トゥーン輪郭線をドットで指定する

	COLOR_F toonColor;//トゥーン輪郭線色

	int blendParam;//0～255

};
