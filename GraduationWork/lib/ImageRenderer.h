#pragma once

#include "typedef.h"
#include "Renderer.h"
#include "Image.h"
#include <string>
#include <vector>

class ImageRenderer : public Renderer {
	friend Image;
public:
	ImageRenderer();
	~ImageRenderer();
	void Draw();

	/// <summary>
	/// 画像を読み込む
	/// </summary>
	/// <param name="_filePass">読込みたい画像ファイルのパス</param>
	/// <returns>読み込み成功でtrue, ファイルが見つからないか既に同じものを読み込んでいたらfalse</returns>
	bool SetImage(const std::string& _filePass);

	/// <summary>
	/// 画像を分割読み込み
	/// </summary>
	/// <param name="_filePass">読込みたい画像ファイルのパス</param>
	/// <param name="_xdiv">横分割数</param>
	/// <param name="_ydiv">縦分割数</param>
	/// <param name="_allnum">全体分割数、0で_xdiv*_ydiv</param>
	/// <returns>true：読み込み成功、false：失敗</returns>
	bool SetImageDiv(const std::string& _filePass, unsigned _xdiv, unsigned _ydiv, unsigned _allnum = 0u);

	/// <summary>
	/// 画像ハンドル取得
	/// </summary>
	/// <returns>画像ハンドル</returns>
	std::vector<int> GetHandle()const { return image.imageInfo->handles; }

	/// <summary>
	/// 描画番号をセット
	/// </summary>
	/// <returns>true：成功、false：範囲外</returns>
	bool SetImageNumber(unsigned _num);

	/// <summary>
	/// 描画番号取得
	/// </summary>
	/// <returns>描画番号</returns>
	unsigned GetDrawNumber()const { return drawNum; }

	/// <summary>
	/// 描画最大番号取得
	/// </summary>
	/// <returns>描画最大番号</returns>
	unsigned GetDrawMaxNumber()const;

	/// <summary>
	/// 読み込んでいるファイルのパスを取得
	/// </summary>
	/// <returns>ファイルパス</returns>
	std::string GetPath()const { return image.path; }

	/// <summary>
	/// 画像Xサイズを取得
	/// </summary>
	/// <returns>読み込み時：画像サイズ、読み込んでいない：-1</returns>
	int GetSizeX()const;

	/// <summary>
	/// 画像Yサイズを取得
	/// </summary>
	/// <returns>読み込み時：画像サイズ、読み込んでいない：-1</returns>
	int GetSizeY()const;

	/// <summary>
	/// 読み込んだデータを破棄
	/// </summary>
	void Release() { image.Destroy(); drawNum = 0u; }

private:
	void Initialize();

	int CheckAsyncLoading() override;

	void DestroyParam()override;

public:
	VECTOR2 position;
	float rotation;
	VECTOR2 scale;
	float alpha;
	int transFlag;
	bool turnXFlag;
	bool turnYFlag;
	int order;

private:
	Image image;

	unsigned drawNum;
};