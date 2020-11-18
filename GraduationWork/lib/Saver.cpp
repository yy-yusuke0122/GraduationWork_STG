#include <fstream>
#include "HiddenType.h"
#include "Loader.h"
#include "Saver.h"

std::unordered_map<std::string, std::string> Saver::info;

bool Saver::isSaving = false;

bool Saver::isAsync = false;

namespace
{
	constexpr unsigned INT_SIZE = sizeof(int);
	static const std::string TAG = "UR_SAVE";
	static const unsigned tag_size = static_cast<unsigned>(TAG.size());
}

namespace
{
	CriticalSection cs;
	uintptr_t hThread = 0;

	Event hEvent;
}

void Saver::DeleteAll()
{
	if (Wait())
		info.clear();
}

void Saver::DeleteKey(const std::string& _key)
{
	if (Wait())
		info.erase(_key);
}

bool Saver::HasKey(const std::string& _key)
{
	if (Wait())
		return info.find(_key) != info.end();
	return false;
}

void Saver::Save()
{
	Wait();
	Loader::Wait();

	LOCK lock(cs);
	isSaving = true;

	if (isAsync)
	{
		hEvent.NonSignal();
		hThread = _beginthreadex(nullptr, 0u, Saving, nullptr, 0u, nullptr);
		if (hThread == 0)
		{
			isAsync = false;
			Saving(nullptr);
		}
	}
	else
		Saving(nullptr);
}

bool Saver::SetInt(const std::string& _key, int _data)
{
	if (Wait())
	{
		info[_key].assign(reinterpret_cast<char*>(&_data), sizeof(int));
		return true;
	}
	return false;
}

bool Saver::SetFloat(const std::string& _key, float _data)
{
	if (Wait())
	{
		info[_key].assign(reinterpret_cast<char*>(&_data), sizeof(float));
		return true;
	}
	return false;
}

bool Saver::SetString(const std::string& _key, const std::string& _data)
{
	if (Wait())
	{
		info[_key] = _data;
		return true;
	}
	return false;
}

bool Saver::IsSaving()
{
	LOCK lock(cs);
	return isSaving;
}

bool Saver::Wait()
{
	LOCK lock(cs);
	if (isSaving)
		return WaitForSingleObject(hEvent.handle, INFINITE) == WAIT_OBJECT_0;
	return true;
}

unsigned Saver::Saving(LPVOID _param)
{
	std::ofstream save("Save\\save.ur", std::ofstream::binary);

	save.write(TAG.c_str(), tag_size);

	//データ数
	unsigned count = static_cast<unsigned>(info.size());

	save.write(reinterpret_cast<char*>(&count), INT_SIZE);

	for (std::unordered_map<std::string, std::string>::iterator it = info.begin(), end = info.end(); it != end; ++it)
	{
		//キーの長さ
		unsigned keyLength = static_cast<unsigned>(it->first.size());
		save.write(reinterpret_cast<char*>(&keyLength), INT_SIZE);

		//キー
		save.write(it->first.c_str(), keyLength);

		//データの長さ
		unsigned dataLength = static_cast<unsigned>(it->second.size());
		save.write(reinterpret_cast<char*>(&dataLength), INT_SIZE);

		//データ
		save.write(it->second.c_str(), dataLength);
	}

	LOCK lock(cs);
	isSaving = false;

	hEvent.Signal();

	return 1u;
}
