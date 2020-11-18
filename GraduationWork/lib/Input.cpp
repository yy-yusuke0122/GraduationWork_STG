#include "Input.h"
#include "dxlib/DxLib.h"

int Input::key[256] = {};
int Input::mouse[5] = {};
std::vector<Input::PAD_INFO> Input::pad;

int Input::mouseX = 0, Input::mouseY = 0;

int Input::mouseWheel = 0;

bool Input::anyKey = false;

namespace
{
	bool isInit = false;

	void Push(int& _input)
	{
		switch (_input)
		{
		case 0:				//break;
		case 1:++_input;	break;
		case 2:				break;
		case 3:_input = 1;	break;
		default:			break;
		}
		Input::anyKey = true;
	}
	void nonPush(int& _input)
	{
		switch (_input)
		{
		case 0:				break;
		case 1:				//break;
		case 2:_input = 3;	break;
		case 3:_input = 0;	break;
		default:
			break;
		}
	}
}

bool Input::Start()
{
	if (!isInit)
	{
		int count = GetJoypadNum();

		if (count)
		{
			pad.resize(count);
		}

		return isInit = true;
	}
	return false;
}

bool Input::End()
{
	if (isInit)
	{
		isInit = false;
		pad.clear();
		return true;
	}
	return false;
}

void Input::Update()
{
	anyKey = false;

	//キー入力

	char buf[256] = {};
	GetHitKeyStateAll(buf);

	for (int i = 0; i < 256; ++i)
	{
		if (buf[i])	Push	(key[i]);
		else		nonPush	(key[i]);
	}

	//マウス入力

	int input = GetMouseInput();

	for (int i = 0; i < 5; ++i)
	{
		if (input & (0x1 << i))	Push	(mouse[i]);
		else					nonPush	(mouse[i]);
	}

	GetMousePoint(&mouseX, &mouseY);

	mouseWheel = GetMouseWheel();

	//パッド入力

	for (int count = 0, size = GetPadCount(); count < size; ++count)
	{
		int type = count + 1;

		input = GetJoypadInputState(type);

		int* p = pad[count].info;

		for (int i = 0; i < 32; ++i)
		{
			if (input & (0x1 << i))
					Push	(p[i]);
			else	nonPush	(p[i]);
		}

		GetJoypadAnalogInput(&p[32], &p[33], type);

	}

}

bool Input::SetMousePos(int _x, int _y)
{
	if (SetMousePoint(_x, _y) == 0)
	{
		mouseX = _x;
		mouseY = _y;
		return true;
	}
	return false;
}

bool Input::SetMouseDisp(bool _isDisp)
{
	return SetMouseDispFlag(_isDisp ? TRUE : FALSE) == 0;
}

bool Input::IsPadDown(int _padCount, PAD _pad)
{
	if (IsPadCountRange(_padCount))
	{
		return pad[_padCount].info[_pad] == 1;
	}
	return false;
}

bool Input::IsPadPush(int _padCount, PAD _pad)
{
	if (IsPadCountRange(_padCount))
	{
		return pad[_padCount].info[_pad] == 2;
	}
	return false;
}

bool Input::IsPadUp(int _padCount, PAD _pad)
{
	if (IsPadCountRange(_padCount))
	{
		return pad[_padCount].info[_pad] == 3;
	}
	return false;
}

bool Input::IsPadNone(int _padCount, PAD _pad)
{
	if (IsPadCountRange(_padCount))
	{
		return pad[_padCount].info[_pad] == 0;
	}
	return false;
}

bool Input::SetPadDeadZone(int _padCount, float _zone)
{
	if (IsPadCountRange(_padCount))
		return SetJoypadDeadZone(_padCount, static_cast<float>(_zone)) == 0;
	return false;
}

bool Input::StartPadVibration(int _padCount, int _power, int _time)
{
	if (IsPadCountRange(_padCount))
	{
		return StartJoypadVibration(_padCount, _power, _time) == 0;
	}
	return false;
}

bool Input::StopPadVibration(int _padCount)
{
	if (IsPadCountRange(_padCount))
	{
		return StopJoypadVibration(_padCount) == 0;
	}
	return false;
}

bool Input::GetPadAnalog(int _padCount, int& _x, int& _y)
{
	if (IsPadCountRange(_padCount))
	{
		_x = pad[_padCount].info[32];
		_y = pad[_padCount].info[33];
		return true;
	}
	return false;
}
