#pragma once

#include <string>

struct MeshRendererInfo;

class Material;

class Texture
{
	friend class MeshRenderer;//速度向上のため

public:
	enum ADDRESS_MODE
	{
		DEFAULT,
		WRAP,
		MIRROR,
		CLAMP,
		BORDER
	};

	enum SAMPLE
	{
		NEAREST,
		BILINEAR,
		ANISOTROPIC
	};

public:
	Texture()
	{
	}

	~Texture()
	{
	}

	void Set();

public:
	/// <summary>
	/// テクスチャ名取得
	/// </summary>
	/// <returns>テクスチャ名</returns>
	std::string GetName()const;

	/// <summary>
	/// モデル内のテクスチャ番号取得
	/// </summary>
	/// <returns>テクスチャ番号</returns>
	int GetNo()const { return no; }

	/// <summary>
	/// UVアドレスモードセット
	/// 失敗時、パラメータはセットされません
	/// </summary>
	/// <param name="_u">Uにセットするアドレスモード</param>
	/// <param name="_v">Vにセットするアドレスモード</param>
	/// <returns>成功：true、失敗：false</returns>
	bool SetMode(int _u, int _v);

	/// <summary>
	/// UVアドレスモード取得
	/// </summary>
	/// <param name="_u">Uアドレスモード格納</param>
	/// <param name="_v">Vアドレスモード格納</param>
	void GetMode(int& _u, int& _v);

	/// <summary>
	/// サンプルセット
	/// </summary>
	/// <param name="_sample">セットするサンプル値</param>
	/// <returns>成功：true、失敗：false</returns>
	bool SetSample(int _sample);

	/// <summary>
	/// サンプル取得
	/// </summary>
	/// <returns>サンプル</returns>
	int GetSample()const { return sample; }

private:
	int no;//番号

	int modeU, modeV;//UVアドレス指定モード

	int sample;

	MeshRendererInfo* info;

public:
	int handle;//画像ハンドル（デフォルトは-1）

};
