#include "Debug.h"
#include <stdio.h>
//#include <consoleapi.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <signal.h>

namespace
{
#if _DEBUG || DEBUG

	bool isOutFlag = false;

#endif // _DEBUG || DEBUG

}

namespace
{
#if DEBUG || _DEBUG
	
	FILE* file = nullptr;

	void ReleaseConsoleWindow()
	{
		//if (file != nullptr)
		//{
		//	fclose(file);
		//	FreeConsole();
		//	file = nullptr;
		//}
	}

	//BOOL WINAPI proc(DWORD _type)
	//{
	//	switch (_type)
	//	{
	//	case CTRL_C_EVENT:
	//	case CTRL_BREAK_EVENT:
	//	case CTRL_CLOSE_EVENT:
	//		return TRUE;
	//	}
	//	return FALSE;
	//}

	void CreateConsoleWindow()
	{
		//if (file == nullptr)
		//{
		//	//コンソールウィンドウ作成
		//	if (!AllocConsole())return;

		//	freopen_s(&file, "CON", "w", stdout);
		//	SetConsoleCtrlHandler(proc, TRUE);//TODO
		//}
	}

#endif // DEBUG || _DEBUG
}

namespace
{
#if _DEBUG || DEBUG

	bool CheckCreateWindow(bool _onlyFlag)
	{
		if ((isOutFlag) || (_onlyFlag == false))
		{
			CreateConsoleWindow();
			return true;
		}
		return false;
	}

#endif // _DEBUG || DEBUG
}

void Debug::Write(int _outdata, bool _isConsoleCreatedOnly)
{
#if _DEBUG || DEBUG

	if (CheckCreateWindow(_isConsoleCreatedOnly))
	{
		printf("%d\n", _outdata);
	}

#endif // _DEBUG || DEBUG
}

void Debug::Write(float _outdata, bool _isConsoleCreatedOnly)
{
#if _DEBUG || DEBUG

	if (CheckCreateWindow(_isConsoleCreatedOnly))
	{
		printf("%f\n", _outdata);
	}

#endif // _DEBUG || DEBUG
}

void Debug::Write(bool _outdata, bool _isConsoleCreatedOnly)
{
#if _DEBUG || DEBUG

	if (CheckCreateWindow(_isConsoleCreatedOnly))
	{
		if (_outdata)
			printf("%s\n", "true");
		else
			printf("%s\n", "false");
	}

#endif // _DEBUG || DEBUG
}

void Debug::Write(const std::string& _outdata, bool _isConsoleCreatedOnly)
{
#if _DEBUG || DEBUG

	if (CheckCreateWindow(_isConsoleCreatedOnly))
	{
		printf("%s\n", _outdata.c_str());
	}

#endif // _DEBUG || DEBUG
}

void Debug::Write(const std::string& _str, int _data, bool _isConsoleCreatedOnly)
{
#if _DEBUG || DEBUG

	if (CheckCreateWindow(_isConsoleCreatedOnly))
	{
		printf("%s%d\n", _str.c_str(), _data);
	}

#endif // _DEBUG || DEBUG
}

void Debug::Write(const std::string& _str, float _data, bool _isConsoleCreatedOnly)
{
#if _DEBUG || DEBUG

	if (CheckCreateWindow(_isConsoleCreatedOnly))
	{
		printf("%s%f\n", _str.c_str(), _data);
	}

#endif // _DEBUG || DEBUG
}

void Debug::Write(const std::string& _str, bool _data, bool _isConsoleCreatedOnly)
{
#if _DEBUG || DEBUG

	if (CheckCreateWindow(_isConsoleCreatedOnly))
	{
		if (_data)
			printf("%s%s\n", _str.c_str(), "true");
		else
			printf("%s%s\n", _str.c_str(), "false");
	}

#endif // _DEBUG || DEBUG
}

void Debug::OutFlag(bool _flag)
{
#if _DEBUG || DEBUG

	isOutFlag = _flag;

	if (isOutFlag)
	{
		CreateConsoleWindow();
	}

#endif // _DEBUG || DEBUG
}

void Debug::Release()
{
#if DEBUG || _DEBUG

	ReleaseConsoleWindow();

#endif // DEBUG || _DEBUG
}

std::string Debug::OutString(int _line, const char* _file, const char* _datastr)
{
	std::string out = "ファイル名：";
	return out.append(_file).append("\n").
		append("行番号：").append(std::to_string(_line)).append("\n").
		append(_datastr).append("：");
}
