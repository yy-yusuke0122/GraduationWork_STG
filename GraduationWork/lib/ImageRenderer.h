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
	void Initialize()override;

	int CheckAsyncLoading() override;

	void DestroyParam()override;

public:
	VECTOR2 position;//画像座標

	float rotation;//画像回転度（rad）
	
	VECTOR2 scale;//画像スケール
	
	int alpha;//透明度（0～255）

	int add;//加算（-1は無効）、描画先と画像の値を足して（0～1）この値を掛けて出力（0～255）

	int sub;//減算（-1は無効）、描画先の値から画像の値を引いて（0～1）この値を掛けて出力（0～255）

	int mul;//乗算する値（-1は無効）、描画先と画像の色（0～1）を乗算した結果にこの値を掛けて出力（0～255）

	int inv;//色反転（-1は無効）、反転後の透明度（0～255）
	
	int transFlag;//画像透明度有効フラグ
	
	bool turnXFlag;//横反転フラグ
	
	bool turnYFlag;//縦反転フラグ
	
	int order;//描画の順番（0が先）

	int red, green, blue;//0～255（色の強さ）

private:
	Image image;

	unsigned drawNum;
};