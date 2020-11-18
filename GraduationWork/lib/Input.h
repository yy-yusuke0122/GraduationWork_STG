#pragma once

#include <vector>

enum KEY
{
	KEY_BACK		= (0x0E),	// BackSpaceキー
	KEY_TAB			= (0x0F),	// Tabキー		
	KEY_ENTER		= (0x1C),	// Enterキー	

	KEY_LSHIFT		= (0x2A),	// 左Shiftキー	
	KEY_RSHIFT		= (0x36),	// 右Shiftキー	
	KEY_LCONTROL	= (0x1D),	// 左Ctrlキー	
	KEY_RCONTROL	= (0x9D),	// 右Ctrlキー	
	KEY_ESCAPE		= (0x01),	// Escキー		
	KEY_SPACE		= (0x39),	// スペースキー	
	KEY_PGUP		= (0xC9),	// PageUpキー	
	KEY_PGDN		= (0xD1),	// PageDownキー	
	KEY_END			= (0xCF),	// Endキー		
	KEY_HOME		= (0xC7),	// Homeキー		
	KEY_LEFT		= (0xCB),	// 左キー		
	KEY_UP			= (0xC8),	// 上キー		
	KEY_RIGHT		= (0xCD),	// 右キー		
	KEY_DOWN		= (0xD0),	// 下キー		
	KEY_INSERT		= (0xD2),	// Insertキー	
	KEY_DELETE		= (0xD3),	// Deleteキー	

	KEY_MINUS		= (0x0C),	// -キー		
	KEY_YEN			= (0x7D),	// \キー		
	KEY_PREVTRACK	= (0x90),	// ^キー		
	KEY_PERIOD		= (0x34),	// .キー		
	KEY_SLASH		= (0x35),	// ＼キー		
	KEY_LALT		= (0x38),	// 左Altキー	
	KEY_RALT		= (0xB8),	// 右Altキー	
	KEY_SCROLL		= (0x46),	// ScrollLockキー
	KEY_SEMICOLON	= (0x27),	// ;キー		
	KEY_COLON		= (0x92),	// :キー		
	KEY_LBRACKET	= (0x1A),	// [キー		
	KEY_RBRACKET	= (0x1B),	// ]キー		
	KEY_AT			= (0x91),	// @キー		
	KEY_BACKSLASH	= (0x2B),	// ＼キー		
	KEY_COMMA		= (0x33),	// ,キー		
	KEY_KANJI		= (0x94),	// 漢字キー		
	KEY_CONVERT		= (0x79),	// 変換キー		
	KEY_NOCONVERT	= (0x7B),	// 無変換キー	
	KEY_KANA		= (0x70),	// カナキー		
	KEY_APPS		= (0xDD),	// アプリケーションメニュ
	KEY_CAPSLOCK	= (0x3A),	// CaspLockキー		
	KEY_SYSRQ		= (0xB7),	// PrintScreenキー	
	KEY_PAUSE		= (0xC5),	// PauseBreakキー	
	KEY_LWIN		= (0xDB),	// 左Winキー		
	KEY_RWIN		= (0xDC),	// 右Winキー		

	KEY_NUMLOCK		= (0x45),	// テンキーNumLockキー	
	KEY_NUMPAD0		= (0x52),	// テンキー0			
	KEY_NUMPAD1		= (0x4F),	// テンキー1			
	KEY_NUMPAD2		= (0x50),	// テンキー2			
	KEY_NUMPAD3		= (0x51),	// テンキー3			
	KEY_NUMPAD4		= (0x4B),	// テンキー4			
	KEY_NUMPAD5		= (0x4C),	// テンキー5			
	KEY_NUMPAD6		= (0x4D),	// テンキー6			
	KEY_NUMPAD7		= (0x47),	// テンキー7			
	KEY_NUMPAD8		= (0x48),	// テンキー8			
	KEY_NUMPAD9		= (0x49),	// テンキー9			
	KEY_MULTIPLY	= (0x37),	// テンキー*キー		
	KEY_ADD			= (0x4E),	// テンキー+キー		
	KEY_SUBTRACT	= (0x4A),	// テンキー-キー		
	KEY_DECIMAL		= (0x53),	// テンキー.キー		
	KEY_DIVIDE		= (0xB5),	// テンキー/キー		
	KEY_NUMPADENTER = (0x9C),	// テンキーのエンターキー

	KEY_F1			= (0x3B),	// F1キー			
	KEY_F2			= (0x3C),	// F2キー			
	KEY_F3			= (0x3D),	// F3キー			
	KEY_F4			= (0x3E),	// F4キー			
	KEY_F5			= (0x3F),	// F5キー			
	KEY_F6			= (0x40),	// F6キー			
	KEY_F7			= (0x41),	// F7キー			
	KEY_F8			= (0x42),	// F8キー			
	KEY_F9			= (0x43),	// F9キー			
	KEY_F10			= (0x44),	// F10キー		
	KEY_F11			= (0x57),	// F11キー		
	KEY_F12			= (0x58),	// F12キー		

	KEY_A			= (0x1E),	// Aキー			
	KEY_B			= (0x30),	// Bキー			
	KEY_C			= (0x2E),	// Cキー			
	KEY_D			= (0x20),	// Dキー			
	KEY_E			= (0x12),	// Eキー			
	KEY_F			= (0x21),	// Fキー			
	KEY_G			= (0x22),	// Gキー			
	KEY_H			= (0x23),	// Hキー			
	KEY_I			= (0x17),	// Iキー			
	KEY_J			= (0x24),	// Jキー			
	KEY_K			= (0x25),	// Kキー			
	KEY_L			= (0x26),	// Lキー			
	KEY_M			= (0x32),	// Mキー			
	KEY_N			= (0x31),	// Nキー			
	KEY_O			= (0x18),	// Oキー			
	KEY_P			= (0x19),	// Pキー			
	KEY_Q			= (0x10),	// Qキー			
	KEY_R			= (0x13),	// Rキー			
	KEY_S			= (0x1F),	// Sキー			
	KEY_T			= (0x14),	// Tキー			
	KEY_U			= (0x16),	// Uキー			
	KEY_V			= (0x2F),	// Vキー			
	KEY_W			= (0x11),	// Wキー			
	KEY_X			= (0x2D),	// Xキー			
	KEY_Y			= (0x15),	// Yキー			
	KEY_Z			= (0x2C),	// Zキー			

	KEY_0			= (0x0B),	// 0キー			
	KEY_1			= (0x02),	// 1キー			
	KEY_2			= (0x03),	// 2キー			
	KEY_3			= (0x04),	// 3キー			
	KEY_4			= (0x05),	// 4キー			
	KEY_5			= (0x06),	// 5キー			
	KEY_6			= (0x07),	// 6キー			
	KEY_7			= (0x08),	// 7キー			
	KEY_8			= (0x09),	// 8キー			
	KEY_9			= (0x0A),	// 9キー			
};

enum MOUSE
{
	MOUSE_LEFT,					// 左ボタン
	MOUSE_RIGHT,				// 右ボタン
	MOUSE_MIDDLE,				// 中央ボタン
	MOUSE_4,					// 4ボタン
	MOUSE_5						// 5ボタン
};

enum PAD
{
	PAD_DOWN,				// ↓チェックマスク
	PAD_LEFT,				// ←チェックマスク
	PAD_RIGHT,				// →チェックマスク
	PAD_UP,					// ↑チェックマスク
	PAD_A,					// Aボタンチェックマスク
	PAD_B,					// Bボタンチェックマスク
	PAD_C,					// Cボタンチェックマスク
	PAD_X,					// Xボタンチェックマスク
	PAD_Y,					// Yボタンチェックマスク
	PAD_Z,					// Zボタンチェックマスク
	PAD_L,					// Lボタンチェックマスク
	PAD_R,					// Rボタンチェックマスク
	PAD_START,				// STARTボタンチェックマスク
	PAD_M,					// Mボタンチェックマスク
	PAD_D,
	PAD_F,
	PAD_G,
	PAD_H,
	PAD_I,
	PAD_J,
	PAD_K,
	PAD_LL,
	PAD_N,
	PAD_O,
	PAD_P,
	PAD_RR,
	PAD_S,
	PAD_T,
	PAD_U,
	PAD_V,
	PAD_W,
	PAD_XX,

	PAD_1 = 4,
	PAD_2,
	PAD_3,
	PAD_4,
	PAD_5,
	PAD_6,
	PAD_7,
	PAD_8,
	PAD_9,
	PAD_10,
	PAD_11,
	PAD_12,
	PAD_13,
	PAD_14,
	PAD_15,
	PAD_16,
	PAD_17,
	PAD_18,
	PAD_19,
	PAD_20,
	PAD_21,
	PAD_22,
	PAD_23,
	PAD_24,
	PAD_25,
	PAD_26,
	PAD_27,
	PAD_28
};

class Input
{
private:
	Input()
	{
	}

	~Input()
	{
	}

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>true：成功、false：初期化済み</returns>
	static bool Start();

	/// <summary>
	/// 終了
	/// </summary>
	/// <returns>true：成功、false：未初期化</returns>
	static bool End();

	/// <summary>
	/// 更新
	/// </summary>
	static void Update();

public://キー入力取得
	/// <summary>
	/// キー押し下げ時trueを返す
	/// </summary>
	/// <param name="_key">取得するキー</param>
	/// <returns>true：押し下げ時、false：それ以外</returns>
	static bool IsKeyDown	(KEY _key) { return key[_key] == 1; }

	/// <summary>
	/// キー押し下げ中trueを返す
	/// </summary>
	/// <param name="_key">取得するキー</param>
	/// <returns>true：押し下げ中、false：それ以外</returns>
	static bool IsKeyPush	(KEY _key) { return key[_key] == 2; }

	/// <summary>
	/// キー押し上げ時trueを返す
	/// </summary>
	/// <param name="_key">取得するキー</param>
	/// <returns>true：押し上げ時、false：それ以外</returns>
	static bool IsKeyUp		(KEY _key) { return key[_key] == 3; }

	/// <summary>
	/// キー入力無しか取得
	/// </summary>
	/// <param name="_key">取得するキー</param>
	/// <returns>true：入力無し、false：入力有り</returns>
	static bool IsKeyNone	(KEY _key) { return key[_key] == 0; }

public://マウス入力取得
	/// <summary>
	/// マウスボタン押し下げ時trueを返す
	/// </summary>
	/// <param name="_mouse">取得するマウスボタン</param>
	/// <returns>true：押し下げ時、false：それ以外</returns>
	static bool IsMouseDown	(MOUSE _mouse) { return mouse[_mouse] == 1; }

	/// <summary>
	/// マウスボタン押し下げ中trueを返す
	/// </summary>
	/// <param name="_mouse">取得するマウスボタン</param>
	/// <returns>true：押し下げ中、false：それ以外</returns>
	static bool IsMousePush	(MOUSE _mouse) { return mouse[_mouse] == 2; }

	/// <summary>
	/// マウスボタン押し上げ時trueを返す
	/// </summary>
	/// <param name="_mouse">取得するマウスボタン</param>
	/// <returns>true：押し上げ時、false：それ以外</returns>
	static bool IsMouseUp	(MOUSE _mouse) { return mouse[_mouse] == 3; }

	/// <summary>
	/// マウスボタン入力無しか取得
	/// </summary>
	/// <param name="_mouse">取得するマウスボタン</param>
	/// <returns>true：入力無し、false：入力有り</returns>
	static bool IsMouseNone	(MOUSE _mouse) { return mouse[_mouse] == 0; }

	/// <summary>
	/// マウスホイールの回転量取得
	/// </summary>
	/// <returns>マウスホイール回転量</returns>
	static int 	GetMouseWheel() { return mouseWheel; }

	/// <summary>
	/// マウス座標取得
	/// </summary>
	/// <param name="_x">マウスx座標格納</param>
	/// <param name="_y">マウスy座標格納</param>
	static void	GetMousePos(int& _x, int& _y) { _x = mouseX; _y = mouseY; }

	/// <summary>
	/// マウス座標取得
	/// </summary>
	/// <param name="_x">マウスx座標格納</param>
	/// <param name="_y">マウスy座標格納</param>
	static void	GetMousePos(float& _x, float& _y) { _x = static_cast<float>(mouseX); _y = static_cast<float>(mouseY); }

	/// <summary>
	/// マウス座標セット
	/// </summary>
	/// <param name="_x">セッするX座標</param>
	/// <param name="_y">セッするY座標</param>
	static bool SetMousePos(int _x, int _y);

	/// <summary>
	/// マウス表示切替
	/// </summary>
	/// <param name="_isDisp">true：表示、false：非表示</param>
	/// <returns>true：成功、false：失敗</returns>
	static bool SetMouseDisp(bool _isDisp);

public://パッド入力取得
	/// <summary>
	/// パッドのボタン押し下げ時trueを返す
	/// </summary>
	/// <param name="_padCount">取得するパッド番号</param>
	/// <param name="_pad">取得するパッドボタン</param>
	/// <returns>true：押し下げ時、false：それ以外</returns>
	static bool IsPadDown	(int _padCount, PAD _pad);

	/// <summary>
	/// パッドのボタン押し下げ中trueを返す
	/// </summary>
	/// <param name="_padCount">取得するパッド番号</param>
	/// <param name="_pad">取得するパッドボタン</param>
	/// <returns>true：押し下げ中、false：それ以外</returns>
	static bool IsPadPush	(int _padCount, PAD _pad);

	/// <summary>
	/// パッドのボタン押し上げ時trueを返す
	/// </summary>
	/// <param name="_padCount">取得するパッド番号</param>
	/// <param name="_pad">取得するパッドボタン</param>
	/// <returns>true：押し上げ時、false：それ以外</returns>
	static bool IsPadUp		(int _padCount, PAD _pad);

	/// <summary>
	/// パッドのボタン入力無しか取得
	/// </summary>
	/// <param name="_padCount">取得するパッド番号</param>
	/// <param name="_pad">取得するパッドボタン</param>
	/// <returns>true：入力無し、false：入力有り</returns>
	static bool IsPadNone	(int _padCount, PAD _pad);

	/// <summary>
	/// パッド数取得
	/// </summary>
	/// <returns>パッド数</returns>
	static int	GetPadCount() { return static_cast<int>(pad.size()); }

	/// <summary>
	/// パッドの有効範囲をセット
	/// </summary>
	/// <param name="_padCount">セットするパッド番号</param>
	/// <param name="_zone">0で無効範囲0%、1で有効範囲100%</param>
	/// <returns>true：成功、false：失敗</returns>
	static bool SetPadDeadZone(int _padCount, float _zone);

	/// <summary>
	/// パッドの振動をセット
	/// </summary>
	/// <param name="_padCount">セットするパッド番号</param>
	/// <param name="_power">振動の強さ</param>
	/// <param name="_time">振動時間（ミリ秒）、-1で無限</param>
	/// <returns>true：成功、false：失敗</returns>
	static bool StartPadVibration(int _padCount, int _power, int _time);

	/// <summary>
	/// パッドの振動を止める
	/// </summary>
	/// <param name="_padCount">セットするパッド番号</param>
	/// <returns>true：成功、false：失敗</returns>
	static bool StopPadVibration(int _padCount);

	/// <summary>
	/// パッドのスティック入力量取得
	/// </summary>
	/// <param name="_padCount">取得するパッド番号</param>
	/// <param name="_x">左右の入力量、-1000～1000</param>
	/// <param name="_y">上下の入力量、-1000～1000</param>
	/// <returns>true：成功、false：失敗</returns>
	static bool GetPadAnalog(int _padCount, int& _x, int& _y);

	/// <summary>
	/// 引数が有効なパッド番号かを取得
	/// </summary>
	/// <param name="_padCount">調べる番号</param>
	/// <returns>true：有効、false：無効</returns>
	static bool IsPadCountRange(int _padCount) { return _padCount >= 0 && GetPadCount() > _padCount; }

private:
	struct PAD_INFO { int info[34]; };

	static int key[256];//キーボード
	static int mouse[5];//マウス
	static std::vector<PAD_INFO> pad;//パッド

	static int mouseX, mouseY;//マウス座標

	static int mouseWheel;//マウスホイール

public:
	static bool anyKey;//何かしらのキー入力

};
