#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "typedef.h"

enum KEY
{
	KEY_BACK		= (0x0E),	// BackSpace�L�[
	KEY_TAB			= (0x0F),	// Tab�L�[		
	KEY_ENTER		= (0x1C),	// Enter�L�[	

	KEY_LSHIFT		= (0x2A),	// ��Shift�L�[	
	KEY_RSHIFT		= (0x36),	// �EShift�L�[	
	KEY_LCONTROL	= (0x1D),	// ��Ctrl�L�[	
	KEY_RCONTROL	= (0x9D),	// �ECtrl�L�[	
	KEY_ESCAPE		= (0x01),	// Esc�L�[		
	KEY_SPACE		= (0x39),	// �X�y�[�X�L�[	
	KEY_PGUP		= (0xC9),	// PageUp�L�[	
	KEY_PGDN		= (0xD1),	// PageDown�L�[	
	KEY_END			= (0xCF),	// End�L�[		
	KEY_HOME		= (0xC7),	// Home�L�[		
	KEY_LEFT		= (0xCB),	// ���L�[		
	KEY_UP			= (0xC8),	// ��L�[		
	KEY_RIGHT		= (0xCD),	// �E�L�[		
	KEY_DOWN		= (0xD0),	// ���L�[		
	KEY_INSERT		= (0xD2),	// Insert�L�[	
	KEY_DELETE		= (0xD3),	// Delete�L�[	

	KEY_MINUS		= (0x0C),	// -�L�[		
	KEY_YEN			= (0x7D),	// \�L�[		
	KEY_PREVTRACK	= (0x90),	// ^�L�[		
	KEY_PERIOD		= (0x34),	// .�L�[		
	KEY_SLASH		= (0x35),	// �_�L�[		
	KEY_LALT		= (0x38),	// ��Alt�L�[	
	KEY_RALT		= (0xB8),	// �EAlt�L�[	
	KEY_SCROLL		= (0x46),	// ScrollLock�L�[
	KEY_SEMICOLON	= (0x27),	// ;�L�[		
	KEY_COLON		= (0x92),	// :�L�[		
	KEY_LBRACKET	= (0x1A),	// [�L�[		
	KEY_RBRACKET	= (0x1B),	// ]�L�[		
	KEY_AT			= (0x91),	// @�L�[		
	KEY_BACKSLASH	= (0x2B),	// �_�L�[		
	KEY_COMMA		= (0x33),	// ,�L�[		
	KEY_KANJI		= (0x94),	// �����L�[		
	KEY_CONVERT		= (0x79),	// �ϊ��L�[		
	KEY_NOCONVERT	= (0x7B),	// ���ϊ��L�[	
	KEY_KANA		= (0x70),	// �J�i�L�[		
	KEY_APPS		= (0xDD),	// �A�v���P�[�V�������j��
	KEY_CAPSLOCK	= (0x3A),	// CaspLock�L�[		
	KEY_SYSRQ		= (0xB7),	// PrintScreen�L�[	
	KEY_PAUSE		= (0xC5),	// PauseBreak�L�[	
	KEY_LWIN		= (0xDB),	// ��Win�L�[		
	KEY_RWIN		= (0xDC),	// �EWin�L�[		

	KEY_NUMLOCK		= (0x45),	// �e���L�[NumLock�L�[	
	KEY_NUMPAD0		= (0x52),	// �e���L�[0			
	KEY_NUMPAD1		= (0x4F),	// �e���L�[1			
	KEY_NUMPAD2		= (0x50),	// �e���L�[2			
	KEY_NUMPAD3		= (0x51),	// �e���L�[3			
	KEY_NUMPAD4		= (0x4B),	// �e���L�[4			
	KEY_NUMPAD5		= (0x4C),	// �e���L�[5			
	KEY_NUMPAD6		= (0x4D),	// �e���L�[6			
	KEY_NUMPAD7		= (0x47),	// �e���L�[7			
	KEY_NUMPAD8		= (0x48),	// �e���L�[8			
	KEY_NUMPAD9		= (0x49),	// �e���L�[9			
	KEY_MULTIPLY	= (0x37),	// �e���L�[*�L�[		
	KEY_ADD			= (0x4E),	// �e���L�[+�L�[		
	KEY_SUBTRACT	= (0x4A),	// �e���L�[-�L�[		
	KEY_DECIMAL		= (0x53),	// �e���L�[.�L�[		
	KEY_DIVIDE		= (0xB5),	// �e���L�[/�L�[		
	KEY_NUMPADENTER = (0x9C),	// �e���L�[�̃G���^�[�L�[

	KEY_F1			= (0x3B),	// F1�L�[			
	KEY_F2			= (0x3C),	// F2�L�[			
	KEY_F3			= (0x3D),	// F3�L�[			
	KEY_F4			= (0x3E),	// F4�L�[			
	KEY_F5			= (0x3F),	// F5�L�[			
	KEY_F6			= (0x40),	// F6�L�[			
	KEY_F7			= (0x41),	// F7�L�[			
	KEY_F8			= (0x42),	// F8�L�[			
	KEY_F9			= (0x43),	// F9�L�[			
	KEY_F10			= (0x44),	// F10�L�[		
	KEY_F11			= (0x57),	// F11�L�[		
	KEY_F12			= (0x58),	// F12�L�[		

	KEY_A			= (0x1E),	// A�L�[			
	KEY_B			= (0x30),	// B�L�[			
	KEY_C			= (0x2E),	// C�L�[			
	KEY_D			= (0x20),	// D�L�[			
	KEY_E			= (0x12),	// E�L�[			
	KEY_F			= (0x21),	// F�L�[			
	KEY_G			= (0x22),	// G�L�[			
	KEY_H			= (0x23),	// H�L�[			
	KEY_I			= (0x17),	// I�L�[			
	KEY_J			= (0x24),	// J�L�[			
	KEY_K			= (0x25),	// K�L�[			
	KEY_L			= (0x26),	// L�L�[			
	KEY_M			= (0x32),	// M�L�[			
	KEY_N			= (0x31),	// N�L�[			
	KEY_O			= (0x18),	// O�L�[			
	KEY_P			= (0x19),	// P�L�[			
	KEY_Q			= (0x10),	// Q�L�[			
	KEY_R			= (0x13),	// R�L�[			
	KEY_S			= (0x1F),	// S�L�[			
	KEY_T			= (0x14),	// T�L�[			
	KEY_U			= (0x16),	// U�L�[			
	KEY_V			= (0x2F),	// V�L�[			
	KEY_W			= (0x11),	// W�L�[			
	KEY_X			= (0x2D),	// X�L�[			
	KEY_Y			= (0x15),	// Y�L�[			
	KEY_Z			= (0x2C),	// Z�L�[			

	KEY_0			= (0x0B),	// 0�L�[			
	KEY_1			= (0x02),	// 1�L�[			
	KEY_2			= (0x03),	// 2�L�[			
	KEY_3			= (0x04),	// 3�L�[			
	KEY_4			= (0x05),	// 4�L�[			
	KEY_5			= (0x06),	// 5�L�[			
	KEY_6			= (0x07),	// 6�L�[			
	KEY_7			= (0x08),	// 7�L�[			
	KEY_8			= (0x09),	// 8�L�[			
	KEY_9			= (0x0A),	// 9�L�[			
};

enum MOUSE
{
	MOUSE_LEFT,					// ���{�^��
	MOUSE_RIGHT,				// �E�{�^��
	MOUSE_MIDDLE,				// �����{�^��
	MOUSE_4,					// 4�{�^��
	MOUSE_5						// 5�{�^��
};

enum PAD
{
	PAD_DOWN,				// ���`�F�b�N�}�X�N
	PAD_LEFT,				// ���`�F�b�N�}�X�N
	PAD_RIGHT,				// ���`�F�b�N�}�X�N
	PAD_UP,					// ���`�F�b�N�}�X�N
	PAD_A,					// A�{�^���`�F�b�N�}�X�N
	PAD_B,					// B�{�^���`�F�b�N�}�X�N
	PAD_C,					// C�{�^���`�F�b�N�}�X�N
	PAD_X,					// X�{�^���`�F�b�N�}�X�N
	PAD_Y,					// Y�{�^���`�F�b�N�}�X�N
	PAD_Z,					// Z�{�^���`�F�b�N�}�X�N
	PAD_L,					// L�{�^���`�F�b�N�}�X�N
	PAD_R,					// R�{�^���`�F�b�N�}�X�N
	PAD_START,				// START�{�^���`�F�b�N�}�X�N
	PAD_M,					// M�{�^���`�F�b�N�}�X�N
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

struct InputInfo
{
	InputInfo() :
		value(0.f), accele(3.f), weak(3.f), dead(0.001f), speed(0.f), isSnap(false) {}
	float value;//���ݒl�i-1�`1�j
	float accele;//�����x
	float weak;//��܂��
	float dead;//0�͈�
	float speed;//���x
	bool isSnap;//���Γ��͂�speed��0�ɂ���
};

class Input
{
	struct Info
	{
		using IsPlus = bool;
		struct PADInfo { int no; PAD pad; IsPlus isplus; };
		std::unordered_map<KEY, IsPlus> keyList;
		std::unordered_map<MOUSE, IsPlus> mouseList;
		std::unordered_map<std::string, PADInfo> padList;
	};

	struct MappingInfo
	{
		InputInfo inputInfo;
		Info info;
	};

private:
	Input()
	{
	}

	~Input()
	{
	}

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <returns>true�F�����Afalse�F�������ς�</returns>
	static bool Start();

	/// <summary>
	/// �I��
	/// </summary>
	/// <returns>true�F�����Afalse�F��������</returns>
	static bool End();

	/// <summary>
	/// �X�V
	/// </summary>
	static void Update();

public://�L�[���͎擾
	/// <summary>
	/// �L�[����������true��Ԃ�
	/// </summary>
	/// <param name="_key">�擾����L�[</param>
	/// <returns>true�F�����������Afalse�F����ȊO</returns>
	static bool IsKeyDown	(KEY _key) { return key[_key] == 1; }

	/// <summary>
	/// �L�[����������true��Ԃ�
	/// </summary>
	/// <param name="_key">�擾����L�[</param>
	/// <returns>true�F�����������Afalse�F����ȊO</returns>
	static bool IsKeyPush	(KEY _key) { return key[_key] == 2; }

	/// <summary>
	/// �L�[�����グ��true��Ԃ�
	/// </summary>
	/// <param name="_key">�擾����L�[</param>
	/// <returns>true�F�����グ���Afalse�F����ȊO</returns>
	static bool IsKeyUp		(KEY _key) { return key[_key] == 3; }

	/// <summary>
	/// �L�[���͖������擾
	/// </summary>
	/// <param name="_key">�擾����L�[</param>
	/// <returns>true�F���͖����Afalse�F���͗L��</returns>
	static bool IsKeyNone	(KEY _key) { return key[_key] == 0; }

public://�}�E�X���͎擾
	/// <summary>
	/// �}�E�X�{�^������������true��Ԃ�
	/// </summary>
	/// <param name="_mouse">�擾����}�E�X�{�^��</param>
	/// <returns>true�F�����������Afalse�F����ȊO</returns>
	static bool IsMouseDown	(MOUSE _mouse) { return mouse[_mouse] == 1; }

	/// <summary>
	/// �}�E�X�{�^������������true��Ԃ�
	/// </summary>
	/// <param name="_mouse">�擾����}�E�X�{�^��</param>
	/// <returns>true�F�����������Afalse�F����ȊO</returns>
	static bool IsMousePush	(MOUSE _mouse) { return mouse[_mouse] == 2; }

	/// <summary>
	/// �}�E�X�{�^�������グ��true��Ԃ�
	/// </summary>
	/// <param name="_mouse">�擾����}�E�X�{�^��</param>
	/// <returns>true�F�����グ���Afalse�F����ȊO</returns>
	static bool IsMouseUp	(MOUSE _mouse) { return mouse[_mouse] == 3; }

	/// <summary>
	/// �}�E�X�{�^�����͖������擾
	/// </summary>
	/// <param name="_mouse">�擾����}�E�X�{�^��</param>
	/// <returns>true�F���͖����Afalse�F���͗L��</returns>
	static bool IsMouseNone	(MOUSE _mouse) { return mouse[_mouse] == 0; }

	/// <summary>
	/// �}�E�X�z�C�[���̉�]�ʎ擾
	/// </summary>
	/// <returns>�}�E�X�z�C�[����]��</returns>
	static int 	GetMouseWheel() { return mouseWheel; }

	/// <summary>
	/// �}�E�X���W�擾
	/// </summary>
	/// <param name="_x">�}�E�Xx���W�i�[</param>
	/// <param name="_y">�}�E�Xy���W�i�[</param>
	static void	GetMousePos(int& _x, int& _y) { _x = mouseX; _y = mouseY; }

	/// <summary>
	/// �}�E�X���W�擾
	/// </summary>
	/// <param name="_x">�}�E�Xx���W�i�[</param>
	/// <param name="_y">�}�E�Xy���W�i�[</param>
	static void	GetMousePos(float& _x, float& _y) { _x = static_cast<float>(mouseX); _y = static_cast<float>(mouseY); }

	/// <summary>
	/// �}�E�X���W�Z�b�g
	/// </summary>
	/// <param name="_x">�Z�b����X���W</param>
	/// <param name="_y">�Z�b����Y���W</param>
	static bool SetMousePos(int _x, int _y);

	/// <summary>
	/// �}�E�X�\���ؑ�
	/// </summary>
	/// <param name="_isDisp">true�F�\���Afalse�F��\��</param>
	/// <returns>true�F�����Afalse�F���s</returns>
	static bool SetMouseDisp(bool _isDisp);

public://�p�b�h���͎擾
	/// <summary>
	/// �p�b�h�̃{�^������������true��Ԃ�
	/// </summary>
	/// <param name="_padCount">�擾����p�b�h�ԍ�</param>
	/// <param name="_pad">�擾����p�b�h�{�^��</param>
	/// <returns>true�F�����������Afalse�F����ȊO</returns>
	static bool IsPadDown	(int _padCount, PAD _pad);

	/// <summary>
	/// �p�b�h�̃{�^������������true��Ԃ�
	/// </summary>
	/// <param name="_padCount">�擾����p�b�h�ԍ�</param>
	/// <param name="_pad">�擾����p�b�h�{�^��</param>
	/// <returns>true�F�����������Afalse�F����ȊO</returns>
	static bool IsPadPush	(int _padCount, PAD _pad);

	/// <summary>
	/// �p�b�h�̃{�^�������グ��true��Ԃ�
	/// </summary>
	/// <param name="_padCount">�擾����p�b�h�ԍ�</param>
	/// <param name="_pad">�擾����p�b�h�{�^��</param>
	/// <returns>true�F�����グ���Afalse�F����ȊO</returns>
	static bool IsPadUp		(int _padCount, PAD _pad);

	/// <summary>
	/// �p�b�h�̃{�^�����͖������擾
	/// </summary>
	/// <param name="_padCount">�擾����p�b�h�ԍ�</param>
	/// <param name="_pad">�擾����p�b�h�{�^��</param>
	/// <returns>true�F���͖����Afalse�F���͗L��</returns>
	static bool IsPadNone	(int _padCount, PAD _pad);

	/// <summary>
	/// �p�b�h���擾
	/// </summary>
	/// <returns>�p�b�h��</returns>
	static int	GetPadCount() { return static_cast<int>(pad.size()); }

	/// <summary>
	/// �p�b�h�̗L���͈͂��Z�b�g
	/// </summary>
	/// <param name="_padCount">�Z�b�g����p�b�h�ԍ�</param>
	/// <param name="_zone">0�ŗL���͈�0%�A1�ŗL���͈�100%</param>
	/// <returns>true�F�����Afalse�F���s</returns>
	static bool SetPadDeadZone(int _padCount, float _zone);

	/// <summary>
	/// �p�b�h�̐U�����Z�b�g
	/// </summary>
	/// <param name="_padCount">�Z�b�g����p�b�h�ԍ�</param>
	/// <param name="_power">�U���̋���</param>
	/// <param name="_time">�U�����ԁi�~���b�j�A-1�Ŗ���</param>
	/// <returns>true�F�����Afalse�F���s</returns>
	static bool StartPadVibration(int _padCount, int _power, int _time);

	/// <summary>
	/// �p�b�h�̐U�����~�߂�
	/// </summary>
	/// <param name="_padCount">�Z�b�g����p�b�h�ԍ�</param>
	/// <returns>true�F�����Afalse�F���s</returns>
	static bool StopPadVibration(int _padCount);

	/// <summary>
	/// �p�b�h�̃X�e�B�b�N���͗ʎ擾
	/// </summary>
	/// <param name="_padCount">�擾����p�b�h�ԍ�</param>
	/// <param name="_x">���E�̓��͗ʁA-1000�`1000</param>
	/// <param name="_y">�㉺�̓��͗ʁA-1000�`1000</param>
	/// <returns>true�F�����Afalse�F���s</returns>
	static bool GetPadAnalog(int _padCount, int& _x, int& _y);

	/// <summary>
	/// �������L���ȃp�b�h�ԍ������擾
	/// </summary>
	/// <param name="_padCount">���ׂ�ԍ�</param>
	/// <returns>true�F�L���Afalse�F����</returns>
	static bool IsPadCountRange(int _padCount) { return _padCount >= 0 && GetPadCount() > _padCount; }

public://���̓}�b�s���O�֐�
	/// <summary>
	/// ���̓}�b�s���O�ɃL�[��ǉ�
	/// </summary>
	/// <param name="_name">�}�b�s���O��</param>
	/// <param name="_key">�ǉ�����L�[</param>
	/// <param name="_isPlus">�v���X������</param>
	static void AddKeyMapping(const std::string& _name, KEY _key, bool _isPlus);

	/// <summary>
	/// ���̓}�b�s���O�Ƀ}�E�X��ǉ�
	/// </summary>
	/// <param name="_name">�}�b�s���O��</param>
	/// <param name="_mouse">�ǉ�����}�E�X</param>
	/// <param name="_isPlus">�v���X������</param>
	static void AddMouseMapping(const std::string& _name, MOUSE _mouse, bool _isPlus);

	/// <summary>
	/// ���̓}�b�s���O�Ƀp�b�h��ǉ�
	/// </summary>
	/// <param name="_name">�}�b�s���O��</param>
	/// <param name="_padCount">�ǉ�����p�b�h�ԍ�</param>
	/// <param name="_pad">�ǉ�����p�b�h</param>
	/// <param name="_isPlus">�v���X������</param>
	static void AddPadMapping(const std::string& _name,int _padCount, PAD _pad, bool _isPlus);

	/// <summary>
	/// ���̓}�b�s���O���폜
	/// </summary>
	/// <param name="_name">�}�b�s���O��</param>
	static void EraseMapping(const std::string& _name);

	/// <summary>
	/// ���̓}�b�s���O����L�[���폜
	/// </summary>
	/// <param name="_name">�}�b�s���O��</param>
	/// <param name="_key">�폜����L�[</param>
	static void EraseKeyMapping(const std::string& _name, KEY _key);

	/// <summary>
	/// ���̓}�b�s���O�Ƀ}�E�X���폜
	/// </summary>
	/// <param name="_name">�}�b�s���O��</param>
	/// <param name="_mouse">�폜����}�E�X</param>
	static void EraseMouseMapping(const std::string& _name, MOUSE _mouse);

	/// <summary>
	/// ���̓}�b�s���O�Ƀp�b�h���폜
	/// </summary>
	/// <param name="_name">�}�b�s���O��</param>
	/// <param name="_padCount">�p�b�h�ԍ�</param>
	/// <param name="_pad">�폜����p�b�h</param>
	static void ErasePadMapping(const std::string& _name, int _padCount, PAD _pad);
	
	/// <summary>
	/// ���̓}�b�s���O�̏��
	/// </summary>
	/// <param name="_name">�}�b�s���O��</param>
	/// <param name="_accele">�Z�b�g��������x�Anull�Ŗ���</param>
	/// <param name="_weak">�Z�b�g���錸���Anull�Ŗ���</param>
	/// <param name="_dead">�Z�b�g����0�ɂ���͈́Anull�Ŗ���</param>
	/// <param name="_isSnap">true�Ŕ��Ε����̓��͎擾���A���݂̒l��0�ɂ���Anull�Ŗ���</param>
	/// <returns>���݂̃C���v�b�g���</returns>
	static InputInfo GetInfo(const std::string& _name, float* _accele = nullptr, float* _weak = nullptr, float* _dead = nullptr, bool* _isSnap = nullptr);

	/// <summary>
	/// �}�b�s���O�����猻�݂̓��͒l���擾
	/// </summary>
	/// <param name="_name">�}�b�s���O��</param>
	/// <returns>���݂̓��͒l�i-1�`1�j</returns>
	static float GetInput(const std::string& _name);

public://�f�t�H���g�}�b�s���O�擾
	/// <summary>
	/// �f�t�H���g����
	/// X+�����FD�A���L�[�A�p�b�h��
	/// X-�����FA�A���L�[�A�p�b�h��
	/// Y+�����FS�A���L�[�A�p�b�h��
	/// Y-�����FW�A���L�[�A�p�b�h��
	/// </summary>
	/// <returns>���͒l</returns>
	static VECTOR2 GetAxis();

private:
	struct PAD_INFO { int info[34]; };

	static int key[256];//�L�[�{�[�h
	static int mouse[5];//�}�E�X
	static std::vector<PAD_INFO> pad;//�p�b�h

	static int mouseX, mouseY;//�}�E�X���W

	static int mouseWheel;//�}�E�X�z�C�[��

	static std::unordered_map<std::string, MappingInfo> mapping;//�}�b�s���O�f�[�^

public:
	static bool anyKey;//��������̓���

};
