#include "Sound.h"
#include "Transform.h"
#include "Function.h"

std::unordered_map<std::string, Sound::INFO> Sound::loadInfo;
std::unordered_map<std::string, Sound::INFO> Sound::load3DInfo;

Sound::~Sound()
{
	if (isAsync)
		GetScene()->EraseAsync(this);
	Release();
}

void Sound::Update()
{
	Set();
}

bool Sound::Load(const std::string& _path)
{
    if (!is3D)
    {
        if (path == _path)return true;
    }

	//ƒ}ƒbƒv‚©‚çŒŸõ

	INFO* p = nullptr;

	std::unordered_map<std::string, INFO>::iterator it = loadInfo.find(_path);
	if (it == loadInfo.end())
	{
		//–¢“o˜^A“Ç‚İ‚ñ‚Å‚©‚ç“o˜^
		int h = LoadSoundMem(_path.c_str());

		if (h == -1)return false;//¸”s‚µ‚½‚çI—¹

		p = &loadInfo[_path];//“o˜^‚µ‚½INFO‚ÌƒAƒhƒŒƒX‚ğ•Û

		p->handle = h;

		if (GetUseASyncLoadFlag())
		{
			GetScene()->AddAsync(this);
			isAsync = true;
		}
	}
	else
	{
		//“o˜^Ï‚İ‚Ìê‡AƒJƒEƒ“ƒg‚ğ‘‚â‚µ‚ÄƒAƒhƒŒƒX‚ğ•Û
		it->second.count += 1;
		p = &it->second;
	}

	Release();//Œ³‚Ì‰æ‘œ‚ğ”jŠü

	soundInfo = p;
	path = _path;
	is3D = false;

	return true;
}

bool Sound::Load3D(const std::string& _path)
{
    if (is3D)
    {
        if (path == _path)return true;
    }

	//ƒ}ƒbƒv‚©‚çŒŸõ

	INFO* p = nullptr;

	std::unordered_map<std::string, INFO>::iterator it = load3DInfo.find(_path);
	if (it == load3DInfo.end())
	{
		//–¢“o˜^A“Ç‚İ‚ñ‚Å‚©‚ç“o˜^
		SetCreate3DSoundFlag(TRUE);

		int h = LoadSoundMem(_path.c_str());
		
		SetCreate3DSoundFlag(FALSE);

		if (h == -1)return false;//¸”s‚µ‚½‚çI—¹

		p = &load3DInfo[_path];//“o˜^‚µ‚½INFO‚ÌƒAƒhƒŒƒX‚ğ•Û

		p->handle = h;

		if (GetUseASyncLoadFlag())
		{
			GetScene()->AddAsync(this);
			isAsync = true;
		}
	}
	else
	{
		//“o˜^Ï‚İ‚Ìê‡AƒJƒEƒ“ƒg‚ğ‘‚â‚µ‚ÄƒAƒhƒŒƒX‚ğ•Û
		it->second.count += 1;
		p = &it->second;
	}

	Release();//Œ³‚Ì‰æ‘œ‚ğ”jŠü

	soundInfo = p;
	path = _path;
	is3D = true;

	return true;
}

bool Sound::Play()
{
	if (soundInfo == nullptr)return false;

	Set();

	if (isLoop)
	{
		if (isLoopPlay)return false;//ƒ‹[ƒvÄ¶‚Ìd‚ËŠ|‚¯‚Í‹Ö~

		if (PlaySoundMem(soundInfo->handle, DX_PLAYTYPE_LOOP) != -1)
		{
			isLoopPlay = true;
			return true;
		}
		return false;
	}

	return PlaySoundMem(soundInfo->handle, DX_PLAYTYPE_BACK) != -1;
}

bool Sound::Stop()
{
	if (soundInfo == nullptr)return false;

	if (StopSoundMem(soundInfo->handle) != -1)
	{
		isLoopPlay = false;
		return true;
	}
    return false;
}

void Sound::Release()
{
	if (soundInfo == nullptr)return;

	if (--soundInfo->count <= 0)
	{
		if (is3D)
		{
			DeleteHandle(load3DInfo);
			load3DInfo.erase(path);
		}
		else
		{
			DeleteHandle(loadInfo);
			loadInfo.erase(path);
		}
	}

	soundInfo = nullptr;
	path.clear();
	isLoopPlay = false;
}

bool Sound::SetReverb(REVERB _preset)
{
	if (soundInfo != nullptr && is3D)
		return Set3DPresetReverbParamSoundMem(_preset, soundInfo->handle) != -1;
	return false;
}

bool Sound::SetReverb(SOUND3D_REVERB_PARAM* _param)
{
	if (_param == nullptr)return false;

	if (soundInfo != nullptr && is3D)
		return Set3DReverbParamSoundMem(_param, soundInfo->handle) != -1;
	return false;
}

bool Sound::SetReverbAll(bool _playSoundOnly)
{
	if (soundInfo != nullptr && is3D)
	{
		SOUND3D_REVERB_PARAM param;

		if (Get3DPresetReverbParamSoundMem(&param, soundInfo->handle) == -1)return false;

		return Set3DReverbParamSoundMemAll(&param, (_playSoundOnly) ? TRUE : FALSE) != -1;
	}
	return false;
}

bool Sound::SetReverbAll(REVERB _preset, bool _playSoundOnly)
{
	return Set3DPresetReverbParamSoundMemAll(_preset, (_playSoundOnly) ? TRUE : FALSE) != -1;
}

bool Sound::SetReverbAll(SOUND3D_REVERB_PARAM* _param, bool _playSoundOnly)
{
	if (_param == nullptr)return false;

	return Set3DReverbParamSoundMemAll(_param, (_playSoundOnly) ? TRUE : FALSE) != -1;
}

int Sound::CheckAsyncLoading()
{
	if (soundInfo == nullptr)
		return false;

	return CheckHandleASyncLoad(soundInfo->handle);
}

void Sound::DestroyParam()
{
	if (is3D)
	{
		load3DInfo.erase(path);
	}
	else
	{
		loadInfo.erase(path);
	}

	soundInfo = nullptr;
	path.clear();
	isLoopPlay = false;
}

void Sound::DeleteHandle(std::unordered_map<std::string, INFO>& _info)
{
	std::unordered_map<std::string, INFO>::iterator it = _info.find(path);
	DeleteSoundMem(it->second.handle);
	_info.erase(it);
}

void Sound::Set()
{
	if (soundInfo == nullptr)return;

	//ƒpƒ‰ƒ[ƒ^İ’è
	Clamp(pan, -255, 255);
	ChangePanSoundMem(pan, soundInfo->handle);

	Clamp(volume, 0, 256);
	ChangeVolumeSoundMem(volume, soundInfo->handle);

	if (is3D)
	{
		Set3DPositionSoundMem(transform->position, soundInfo->handle);

		Set3DRadiusSoundMem(radius, soundInfo->handle);

		Set3DVelocitySoundMem(velocity, soundInfo->handle);
	}
}
