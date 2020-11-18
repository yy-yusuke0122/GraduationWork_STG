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
	/// �R���\�[���E�B���h�E��int�l���o��
	/// �t�@�C�����A�s�ԍ��o�͖���
	/// </summary>
	/// <param name="_outdata">�o�͂���f�[�^</param>
	/// <param name="_isConsoleCreatedOnly">false�FOutFlag�Ɋւ�炸�o�́Atrue�FOutFlag��true�̂ݏo��</param>
	static void Write(int _outdata, bool _isConsoleCreatedOnly);

	/// <summary>
	/// �R���\�[���E�B���h�E��float�l���o��
	/// �t�@�C�����A�s�ԍ��o�͖���
	/// </summary>
	/// <param name="_outdata">�o�͂���f�[�^</param>
	/// <param name="_isConsoleCreatedOnly">false�FOutFlag�Ɋւ�炸�o�́Atrue�FOutFlag��true�̂ݏo��</param>
	static void Write(float _outdata, bool _isConsoleCreatedOnly);

	/// <summary>
	/// �R���\�[���E�B���h�E��bool�l���o��
	/// �t�@�C�����A�s�ԍ��o�͖���
	/// </summary>
	/// <param name="_outdata">�o�͂���f�[�^</param>
	/// <param name="_isConsoleCreatedOnly">false�FOutFlag�Ɋւ�炸�o�́Atrue�FOutFlag��true�̂ݏo��</param>
	static void Write(bool _outdata, bool _isConsoleCreatedOnly);

	/// <summary>
	/// �R���\�[���E�B���h�E�ɕ�������o��
	/// �t�@�C�����A�s�ԍ��o�͖���
	/// </summary>
	/// <param name="_outdata">�o�͂���f�[�^</param>
	/// <param name="_isConsoleCreatedOnly">false�FOutFlag�Ɋւ�炸�o�́Atrue�FOutFlag��true�̂ݏo��</param>
	static void Write(const std::string& _outdata, bool _isConsoleCreatedOnly);

	/// <summary>
	/// �R���\�[���E�B���h�E�ɕ�����Aint�l���o��
	/// �t�@�C�����A�s�ԍ��o�͖���
	/// </summary>
	/// <param name="_str">�o�͂��镶����</param>
	/// <param name="_data">�o�͂���int�l</param>
	/// <param name="_isConsoleCreatedOnly">false�FOutFlag�Ɋւ�炸�o�́Atrue�FOutFlag��true�̂ݏo��</param>
	static void Write(const std::string& _str, int _data, bool _isConsoleCreatedOnly);

	/// <summary>
	/// �R���\�[���E�B���h�E�ɕ�����Afloat�l���o��
	/// �t�@�C�����A�s�ԍ��o�͖���
	/// </summary>
	/// <param name="_str">�o�͂��镶����</param>
	/// <param name="_data">�o�͂���float�l</param>
	/// <param name="_isConsoleCreatedOnly">false�FOutFlag�Ɋւ�炸�o�́Atrue�FOutFlag��true�̂ݏo��</param>
	static void Write(const std::string& _str, float _data, bool _isConsoleCreatedOnly);

	/// <summary>
	/// �R���\�[���E�B���h�E�ɕ�����Abool�l���o��
	/// �t�@�C�����A�s�ԍ��o�͖���
	/// </summary>
	/// <param name="_str">�o�͂��镶����</param>
	/// <param name="_data">�o�͂���bool�l</param>
	/// <param name="_isConsoleCreatedOnly">false�FOutFlag�Ɋւ�炸�o�́Atrue�FOutFlag��true�̂ݏo��</param>
	static void Write(const std::string& _str, bool _data, bool _isConsoleCreatedOnly);

	/// <summary>
	/// �R���\�[���E�B���h�E��int�l���o��
	/// </summary>
	/// <param name="_data">�o�͂���int�l</param>
	/// <param name="_line">�s�ԍ�</param>
	/// <param name="_file">�t�@�C����</param>
	/// <param name="_datastr">�f�[�^��</param>
	/// <param name="_isConsoleCreatedOnly">false�FOutFlag�Ɋւ�炸�o�́Atrue�FOutFlag��true�̂ݏo��</param>
	static void Log(int _data, int _line, const char* _file, const char*_datastr, bool _isConsoleCreatedOnly = false)
	{
#if DEBUG || _DEBUG

		Write(OutString(_line, _file, _datastr), _data, _isConsoleCreatedOnly);

#endif // DEBUG || _DEBUG
	}

	/// <summary>
	/// �R���\�[���E�B���h�E��float�l���o��
	/// </summary>
	/// <param name="_data">�o�͂���float�l</param>
	/// <param name="_line">�s�ԍ�</param>
	/// <param name="_file">�t�@�C����</param>
	/// <param name="_datastr">�f�[�^��</param>
	/// <param name="_isConsoleCreatedOnly">false�FOutFlag�Ɋւ�炸�o�́Atrue�FOutFlag��true�̂ݏo��</param>
	static void Log(float _data, int _line, const char* _file, const char* _datastr, bool _isConsoleCreatedOnly = false)
	{
#if DEBUG || _DEBUG

		Write(OutString(_line, _file, _datastr), _data, _isConsoleCreatedOnly);

#endif // DEBUG || _DEBUG
	}

	/// <summary>
	/// �R���\�[���E�B���h�E��bool�l���o��
	/// </summary>
	/// <param name="_data">�o�͂���bool�l</param>
	/// <param name="_line">�s�ԍ�</param>
	/// <param name="_file">�t�@�C����</param>
	/// <param name="_datastr">�f�[�^��</param>
	/// <param name="_isConsoleCreatedOnly">false�FOutFlag�Ɋւ�炸�o�́Atrue�FOutFlag��true�̂ݏo��</param>
	static void Log(bool _data, int _line, const char* _file, const char* _datastr, bool _isConsoleCreatedOnly = false)
	{
#if DEBUG || _DEBUG

		Write(OutString(_line, _file, _datastr), _data, _isConsoleCreatedOnly);

#endif // DEBUG || _DEBUG
	}

	/// <summary>
	/// �R���\�[���E�B���h�E�ɕ�������o��
	/// </summary>
	/// <param name="_data">�o�͂��镶����l</param>
	/// <param name="_line">�s�ԍ�</param>
	/// <param name="_file">�t�@�C����</param>
	/// <param name="_datastr">�f�[�^��</param>
	/// <param name="_isConsoleCreatedOnly">false�FOutFlag�Ɋւ�炸�o�́Atrue�FOutFlag��true�̂ݏo��</param>
	static void Log(const std::string& _data, int _line, const char* _file, const char* _datastr, bool _isConsoleCreatedOnly = false)
	{
#if DEBUG || _DEBUG

		Write(OutString(_line, _file, _datastr) + _data, _isConsoleCreatedOnly);

#endif // DEBUG || _DEBUG
	}

	/// <summary>
	/// �\���t���O���Z�b�g
	/// </summary>
	/// <param name="_flag">�Z�b�g����\���t���O</param>
	static void OutFlag(bool _flag);

	/// <summary>
	/// �f�o�b�O�E�B���h�E�j��
	/// </summary>
	static void Release();

private:
	static std::string OutString(int _line, const char* _file, const char* _datastr);

};
