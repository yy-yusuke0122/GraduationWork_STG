#pragma once
#include "GameObject.h"
#include <string>
#include <unordered_map>
#include "typedef.h"

class ImageRenderer;
class UpdateButton;
class BoxCollider2D;

class UI : public GameObject {
public:
	UI();
	virtual ~UI();
	virtual void Start();

private:

};

class Text : public UI {
public:
	Text();
	~Text();

	/// <summary>
	/// フォントデータを生成する
	/// </summary>
	/// <returns>-1:失敗, 0以上:フォントデータ</returns>
	int SetNewFont(char* FontName, int Size, int Thick, int FontType);

	/// <summary>
	/// 文字列を描画
	/// </summary>
	/// <param name="_position">描画する2次元座標</param>
	/// <returns>0:成功, -1:エラー発生</returns>
	int Draw(VECTOR2 _position);

	/// <summary>
	/// 使用している文字列ハンドルを取得
	/// </summary>
	/// <returns>-1:デフォルトのフォント</returns>
	int GetHandle() const { return handle; }

	/// <summary>
	/// フォントサイズを変更する
	/// </summary>
	/// <param name="_size">フォントサイズ</param>
	/// <returns>-1:失敗, 0以上:成功</returns>
	int SetFontSize(int _size);

	/// <summary>
	/// フォントの太さを変更する
	/// </summary>
	/// <param name="_thick">0～9, -1でデフォルト</param>
	/// <returns>-1:失敗, 0以上:成功</returns>
	int SetFontThick(int _thick);

	/// <summary>
	/// フォントタイプを変更する
	/// </summary>
	/// <param name="_type">
	/// -1でデフォルト(DX_FONTTYPE_NORMALと同じ)
	/// DX_FONTTYPE_NORMAL　　　　　		: ノーマルフォント
	/// DX_FONTTYPE_EDGE　　　　　　　　	: エッジつきフォント
	/// DX_FONTTYPE_ANTIALIASING　　　　	: アンチエイリアスフォント
	/// DX_FONTTYPE_ANTIALIASING_4X4　　　	: アンチエイリアスフォント(4x4サンプリング)
	/// DX_FONTTYPE_ANTIALIASING_8X8　　　	: アンチエイリアスフォント(8x8サンプリング)
	/// DX_FONTTYPE_ANTIALIASING_EDGE_4X4　 : アンチエイリアス＆エッジ付きフォント(4x4サンプリング)
	/// DX_FONTTYPE_ANTIALIASING_EDGE_8X8　 : アンチエイリアス＆エッジ付きフォント(8x8サンプリング) )
	/// </param>
	/// <returns>-1:失敗, 0以上:成功</returns>
	int SetFontType(int _type);

	/// <summary>
	/// 描画する文字列の色を設定する
	/// </summary>
	/// <param name="_color">文字列の色を示すカラーコード</param>
	void SetColor(unsigned int _color);

	std::string text;

private:
	int handle;
	char* fontName;
	int size;
	int thick;
	int fontType;
	unsigned int color;
};

class Button : public UI {
public:
	Button();
	~Button();
	void Start();

	Text* textObj;

private:
	ImageRenderer* image;
	UpdateButton* updater;
};