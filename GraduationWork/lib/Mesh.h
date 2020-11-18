#pragma once

#include "dxlib/DxLib.h"

struct MeshRendererInfo;

class MeshRenderer;

class Material;

class Mesh
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
	Mesh();

	~Mesh()
	{
	}

	void Set();

public:
	/// <summary>
	/// モデル内のメッシュ番号取得
	/// </summary>
	/// <returns>メッシュ番号</returns>
	int GetNo()const { return no; }

	/// <summary>
	/// 半透明要素が含まれているか
	/// </summary>
	/// <returns>true：含まれている、false：含まれていない</returns>
	bool IsSemiTrans()const;

	/// <summary>
	/// メッシュに使われているマテリアル取得
	/// </summary>
	/// <returns>null以外：使用マテリアル、null：使用していない</returns>
	Material* GetMaterial()const;

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

public:
	COLOR_F
		diffuse, //拡散スケール（0～1）
		specular, //鏡面スケール（0～1）
		ambient, //環境スケール（0～1）
		emissive;//自己発光色スケール（0～1）

	bool isDisp;//表示

	float alpha;//0～1

	int blendParam;//0～255

private:
	MeshRendererInfo* info;

	MeshRenderer* renderer;

	int no;//番号

	int blendMode;

};
