#include "Input.h"
#include "Time.h"
#include "Function.h"
#include "dxlib/DxLib.h"

int Input::key[256] = {};
int Input::mouse[5] = {};
std::vector<Input::PAD_INFO> Input::pad;

int Input::mouseX = 0, Input::mouseY = 0;

int Input::mouseWheel = 0;

std::unordered_map<std::string, Input::MappingInfo> Input::mapping;

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

		AddKeyMapping("X", KEY::KEY_D,		true);
		AddKeyMapping("X", KEY::KEY_A,		false);
		AddKeyMapping("X", KEY::KEY_RIGHT,	true);
		AddKeyMapping("X", KEY::KEY_LEFT,	false);

		AddKeyMapping("Y", KEY::KEY_W,		true);
		AddKeyMapping("Y", KEY::KEY_S,		false);
		AddKeyMapping("Y", KEY::KEY_UP,		true);
		AddKeyMapping("Y", KEY::KEY_DOWN,	false);

		AddPadMapping("X", 0, PAD::PAD_RIGHT, true);
		AddPadMapping("X", 0, PAD::PAD_LEFT,  false);

		AddPadMapping("Y", 0, PAD::PAD_UP,	  true);
		AddPadMapping("Y", 0, PAD::PAD_DOWN,  false);

		isInit = true;
		
		return true;
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

	//マッピングの更新
	for (std::unordered_map<std::string, Input::MappingInfo>::iterator ait = mapping.begin(),
		aend = mapping.end(); ait != aend; ++ait)
	{
		bool isplus  = false;
		bool isminus = false;

		Info&  info = ait->second.info;

		//キーマッピング
		for (std::unordered_map<KEY, bool>::iterator kit = info.keyList.begin(),
			kend = info.keyList.end(); kit != kend; ++kit)
		{
			if ( ! IsKeyNone(kit->first))
			{
				if (kit->second)isplus = true;
				else isminus = true;
			}
		}

		//マウスマッピング
		if (isplus && isminus)continue;
		for (std::unordered_map<MOUSE, bool>::iterator mit = info.mouseList.begin(),
			mend = info.mouseList.end(); mit != mend; ++mit)
		{
			if ( ! IsMouseNone(mit->first))
			{
				if (mit->second)isplus = true;
				else isminus = true;
			}
		}

		//パッドマッピング
		if (isplus && isminus)continue;
		for (std::unordered_map<std::string, Info::PADInfo>::iterator pit = info.padList.begin(),
			pend = info.padList.end(); pit != pend; ++pit)
		{
			if ( ! IsPadNone(pit->second.no, pit->second.pad))
			{
				if (pit->second.isplus)isplus = true;
				else isminus = true;
			}
		}

		if (isplus && isminus)continue;

		InputInfo& input = ait->second.inputInfo;

		float delta = Time::DeltaTime();

		if (isplus)
		{
			//プラス
			if (input.isSnap && input.value < 0.f)
			{
				input.value = 0.f;
			}
			input.speed += input.accele * delta;
			if (input.speed > 10000.f)input.speed = 10000.f;//上限
		}
		else if (isminus)
		{
			//マイナス
			if (input.isSnap && input.value > 0.f)
			{
				input.value = 0.f;
			}
			input.speed -= input.accele * delta;
			if (input.speed < -10000.f)input.speed = -10000.f;//下限
		}
		else
		{
			float weak = input.weak * delta;

			//減速
			if (input.value > 0.f)
			{
				input.value -= weak;
				if (input.value < input.dead)
					input.value = 0.f;
			}
			else
			{
				input.value += weak;
				if (input.value > input.dead)
					input.value = 0.f;
			}
			input.speed = 0.f;
		}

		input.value += input.speed * delta;		

		Clamp(input.value, -1.f, 1.f);
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
	return true;
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

void Input::AddKeyMapping(const std::string& _name, KEY _key, bool _isPlus)
{
	mapping[_name].info.keyList[_key] = _isPlus;
}

void Input::AddMouseMapping(const std::string& _name, MOUSE _mouse, bool _isPlus)
{
	mapping[_name].info.mouseList[_mouse] = _isPlus;
}

void Input::AddPadMapping(const std::string& _name, int _padCount, PAD _pad, bool _isPlus)
{
	std::string str = std::to_string(_padCount) + "_" + std::to_string(_pad);
	Info::PADInfo* p = &mapping[_name].info.padList[str];
	p->isplus = _isPlus;
	p->no = _padCount;
	p->pad = _pad;
}

void Input::EraseMapping(const std::string& _name)
{
	mapping.erase(_name);
}

void Input::EraseKeyMapping(const std::string& _name, KEY _key)
{
	mapping[_name].info .keyList.erase(_key);
}

void Input::EraseMouseMapping(const std::string& _name, MOUSE _mouse)
{
	mapping[_name].info .mouseList.erase(_mouse);
}

void Input::ErasePadMapping(const std::string& _name, int _padCount, PAD _pad)
{
	mapping[_name].info .padList.erase(std::to_string(_padCount) + "_" + std::to_string(_pad));
}

InputInfo Input::GetInfo(const std::string& _name, float* _accele, float* _weak, float* _dead, bool* _isSnap)
{
	InputInfo& info = mapping[_name].inputInfo;
	if (_accele != nullptr)info.accele = *_accele;
	if (_weak != nullptr)info.weak = *_weak;
	if (_dead != nullptr)info.dead = *_dead;
	if (_isSnap != nullptr)info.isSnap = *_isSnap;
	return info;
}

float Input::GetInput(const std::string& _name)
{
	std::unordered_map<std::string, MappingInfo>::iterator it = mapping.find(_name);
	if (it == mapping.end())
		return 0.0f;
	return it->second.inputInfo.value;
}

VECTOR2 Input::GetAxis()
{
	return VECTOR2(mapping["X"].inputInfo.value, mapping["Y"].inputInfo.value);
}
