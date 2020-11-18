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
	friend MeshRenderer;//速度向上のため

public:
	Bone();

	~Bone()
	{
	}

	void Set();

public:
	/// <summary>
	/// ボーン名取得
	/// </summary>
	/// <returns>ボーン名</returns>
	std::string GetName()const;

	/// <summary>
	/// モデル内のボーン番号取得
	/// </summary>
	/// <returns>ボーン番号</returns>
	int GetNo()const { return no; }

	/// <summary>
	/// 親ボーン取得
	/// </summary>
	/// <returns>null以外：親ボーン、null：親ボーン存在はしない</returns>
	Bone* GetParent();

	/// <summary>
	/// 子ボーンの数取得
	/// </summary>
	/// <returns>子ボーンの数</returns>
	unsigned GetChildCount()const;

	/// <summary>
	/// 子ボーン取得
	/// </summary>
	/// <param name="_count">取得する子番号</param>
	/// <returns>null以外：子ボーン、null：子ボーン存在はしない</returns>
	Bone* GetChild(unsigned _count);

	/// <summary>
	/// 子ボーン取得
	/// </summary>
	/// <param name="_name">取得する子の名前</param>
	/// <returns>null以外：子ボーン、null：子ボーン存在はしない</returns>
	Bone* GetChild(const std::string& _name);

	/// <summary>
	/// 半透明要素が含まれているか
	/// </summary>
	/// <returns>true：含まれている、false：含まれていない</returns>
	bool IsSemiTrans()const;

	/// <summary>
	/// ボーンのワールド座標取得
	/// </summary>
	/// <returns>ワールド座標</returns>
	VECTOR3 GetWorldPosition()const;

	/// <summary>
	/// ボーンのワールド変換行列取得
	/// </summary>
	/// <returns>ワールド変換行列</returns>
	MATRIX GetWorldMatrix()const;

	/// <summary>
	/// ボーンに含まれるメッシュ数を取得
	/// </summary>
	/// <returns>メッシュ数を取得</returns>
	unsigned GetMeshCount()const;

	/// <summary>
	/// ボーンに含まれるメッシュ取得
	/// </summary>
	/// <param name="_count">ボーン内のメッシュ番号</param>
	/// <returns>null以外：メッシュ、null：メッシュが存在しない</returns>
	Mesh* GetMesh(unsigned _count);

private:
	int no;//番号

	MeshRendererInfo* info;

	std::vector<Mesh> meshes;

	MeshRenderer* renderer;

public:
	bool isDisp;//表示

	COLOR_F
		diffuse, //拡散スケール（0～1）
		specular, //鏡面スケール（0～1）
		ambient, //環境スケール（0～1）
		emissive;//自己発光色スケール（0～1）

	float alpha;//0～1

};
