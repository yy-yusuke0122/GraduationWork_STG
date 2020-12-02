#pragma once

#include <unordered_map>
#include <vector>

class ImageRenderer;

class Image
{
	struct INFO
	{
		INFO() : count(1) {}
		std::vector<int> handles;//画像ハンドル
		int count;
		int sizeX, sizeY;//画像縦横サイズ
	};

public:
	Image(ImageRenderer* _p) :
		imageInfo(nullptr), isDiv(false), renderer(_p)
	{
	}

	~Image()
	{
		Destroy();
	}

	/// <summary>
	/// 画像読み込み
	/// </summary>
	/// <param name="_path">ファイルパス</param>
	/// <returns>true：読み込み成功、false：失敗</returns>
	bool Load(const std::string& _path);

	/// <summary>
	/// 分割画像読み込み
	/// </summary>
	/// <param name="_path">ファイルパス</param>
	/// <param name="_xdiv">横分割数</param>
	/// <param name="_ydiv">縦分割数</param>
	/// <param name="_allnum">全体分割数、0で_xdiv*_ydiv</param>
	/// <returns>true：読み込み成功、false：失敗</returns>
	bool LoadDiv(const std::string& _path, unsigned _xdiv, unsigned _ydiv, unsigned _allnum = 0u);

	/// <summary>
	/// 読み込んだデータを破棄
	/// </summary>
	void Destroy();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(INFO*_p);

	void DestroyParam();

private:
	void Destroy(std::unordered_map<std::string, Image::INFO>& _info);

	void AsyncLoad();

public:
	INFO* imageInfo;
	std::string path;//ファイルパス

	bool isDiv;//分割読み込みか

private:
	ImageRenderer* renderer;

	static std::unordered_map<std::string, INFO> loadInfo;//ファイルパスと参照数を関連付ける
	static std::unordered_map<std::string, INFO> loadDivInfo;//ファイルパスと参照数を関連付ける（分割読み込み用）

};
