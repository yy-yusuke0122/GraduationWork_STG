#pragma once

//TODO

#include <string>

#if _DEBUG || DEBUG


#ifndef DEBUG_LOG

#define DEBUG_LOG(_log) Debug::Log(_log, __LINE__, __FILE__, #_log)

#endif // !DEBUG_LOG


#else


#ifndef DEBUG_LOG

#define DEBUG_LOG(_log) (void)0

#endif // !DEBUG_LOG


#endif // _DEBUG || DEBUG


class Debug
{
private:
	Debug()
	{
	}

	~Debug()
	{
	}

public:
	/// <summary>
	/// コンソールウィンドウにint値を出力
	/// ファイル名、行番号出力無し
	/// </summary>
	/// <param name="_outdata">出力するデータ</param>
	/// <param name="_isConsoleCreatedOnly">false：OutFlagに関わらず出力、true：OutFlagがtrueのみ出力</param>
	static void Write(int _outdata, bool _isConsoleCreatedOnly);

	/// <summary>
	/// コンソールウィンドウにfloat値を出力
	/// ファイル名、行番号出力無し
	/// </summary>
	/// <param name="_outdata">出力するデータ</param>
	/// <param name="_isConsoleCreatedOnly">false：OutFlagに関わらず出力、true：OutFlagがtrueのみ出力</param>
	static void Write(float _outdata, bool _isConsoleCreatedOnly);

	/// <summary>
	/// コンソールウィンドウにbool値を出力
	/// ファイル名、行番号出力無し
	/// </summary>
	/// <param name="_outdata">出力するデータ</param>
	/// <param name="_isConsoleCreatedOnly">false：OutFlagに関わらず出力、true：OutFlagがtrueのみ出力</param>
	static void Write(bool _outdata, bool _isConsoleCreatedOnly);

	/// <summary>
	/// コンソールウィンドウに文字列を出力
	/// ファイル名、行番号出力無し
	/// </summary>
	/// <param name="_outdata">出力するデータ</param>
	/// <param name="_isConsoleCreatedOnly">false：OutFlagに関わらず出力、true：OutFlagがtrueのみ出力</param>
	static void Write(const std::string& _outdata, bool _isConsoleCreatedOnly);

	/// <summary>
	/// コンソールウィンドウに文字列、int値を出力
	/// ファイル名、行番号出力無し
	/// </summary>
	/// <param name="_str">出力する文字列</param>
	/// <param name="_data">出力するint値</param>
	/// <param name="_isConsoleCreatedOnly">false：OutFlagに関わらず出力、true：OutFlagがtrueのみ出力</param>
	static void Write(const std::string& _str, int _data, bool _isConsoleCreatedOnly);

	/// <summary>
	/// コンソールウィンドウに文字列、float値を出力
	/// ファイル名、行番号出力無し
	/// </summary>
	/// <param name="_str">出力する文字列</param>
	/// <param name="_data">出力するfloat値</param>
	/// <param name="_isConsoleCreatedOnly">false：OutFlagに関わらず出力、true：OutFlagがtrueのみ出力</param>
	static void Write(const std::string& _str, float _data, bool _isConsoleCreatedOnly);

	/// <summary>
	/// コンソールウィンドウに文字列、bool値を出力
	/// ファイル名、行番号出力無し
	/// </summary>
	/// <param name="_str">出力する文字列</param>
	/// <param name="_data">出力するbool値</param>
	/// <param name="_isConsoleCreatedOnly">false：OutFlagに関わらず出力、true：OutFlagがtrueのみ出力</param>
	static void Write(const std::string& _str, bool _data, bool _isConsoleCreatedOnly);

	/// <summary>
	/// コンソールウィンドウにint値を出力
	/// </summary>
	/// <param name="_data">出力するint値</param>
	/// <param name="_line">行番号</param>
	/// <param name="_file">ファイル名</param>
	/// <param name="_datastr">データ名</param>
	/// <param name="_isConsoleCreatedOnly">false：OutFlagに関わらず出力、true：OutFlagがtrueのみ出力</param>
	static void Log(int _data, int _line, const char* _file, const char*_datastr, bool _isConsoleCreatedOnly = false)
	{
#if DEBUG || _DEBUG

		Write(OutString(_line, _file, _datastr), _data, _isConsoleCreatedOnly);

#endif // DEBUG || _DEBUG
	}

	/// <summary>
	/// コンソールウィンドウにfloat値を出力
	/// </summary>
	/// <param name="_data">出力するfloat値</param>
	/// <param name="_line">行番号</param>
	/// <param name="_file">ファイル名</param>
	/// <param name="_datastr">データ名</param>
	/// <param name="_isConsoleCreatedOnly">false：OutFlagに関わらず出力、true：OutFlagがtrueのみ出力</param>
	static void Log(float _data, int _line, const char* _file, const char* _datastr, bool _isConsoleCreatedOnly = false)
	{
#if DEBUG || _DEBUG

		Write(OutString(_line, _file, _datastr), _data, _isConsoleCreatedOnly);

#endif // DEBUG || _DEBUG
	}

	/// <summary>
	/// コンソールウィンドウにbool値を出力
	/// </summary>
	/// <param name="_data">出力するbool値</param>
	/// <param name="_line">行番号</param>
	/// <param name="_file">ファイル名</param>
	/// <param name="_datastr">データ名</param>
	/// <param name="_isConsoleCreatedOnly">false：OutFlagに関わらず出力、true：OutFlagがtrueのみ出力</param>
	static void Log(bool _data, int _line, const char* _file, const char* _datastr, bool _isConsoleCreatedOnly = false)
	{
#if DEBUG || _DEBUG

		Write(OutString(_line, _file, _datastr), _data, _isConsoleCreatedOnly);

#endif // DEBUG || _DEBUG
	}

	/// <summary>
	/// コンソールウィンドウに文字列を出力
	/// </summary>
	/// <param name="_data">出力する文字列値</param>
	/// <param name="_line">行番号</param>
	/// <param name="_file">ファイル名</param>
	/// <param name="_datastr">データ名</param>
	/// <param name="_isConsoleCreatedOnly">false：OutFlagに関わらず出力、true：OutFlagがtrueのみ出力</param>
	static void Log(const std::string& _data, int _line, const char* _file, const char* _datastr, bool _isConsoleCreatedOnly = false)
	{
#if DEBUG || _DEBUG

		Write(OutString(_line, _file, _datastr) + _data, _isConsoleCreatedOnly);

#endif // DEBUG || _DEBUG
	}

	/// <summary>
	/// 表示フラグをセット
	/// </summary>
	/// <param name="_flag">セットする表示フラグ</param>
	static void OutFlag(bool _flag);

	/// <summary>
	/// デバッグウィンドウ破棄
	/// </summary>
	static void Release();

private:
	static std::string OutString(int _line, const char* _file, const char* _datastr);

};
