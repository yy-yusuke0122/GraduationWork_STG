#include <fstream>
#include "HiddenType.h"
#include "Saver.h"
#include "Loader.h"

std::unordered_map<std::string, std::string> Loader::info;

bool Loader::isLoading = false;

bool Loader::isAsync = false;

namespace
{
	constexpr unsigned INT_SIZE = sizeof(int);
	static const std::string check = "UR_SAVE";
	static const unsigned check_size = static_cast<unsigned>(check.size());
}

namespace
{
	Event hEvent;
	uintptr_t hThread = 0;

	CriticalSection cs;
}

void Loader::DeleteAll()
{
	if (Wait())
		info.clear();
}

void Loader::DeleteKey(const std::string& _key)
{
	if (Wait())
		info.erase(_key);
}

bool Loader::HasKey(const std::string& _key)
{
	if (Wait())
		return info.find(_key) != info.end();
	return false;
}

void Loader::Load()
{
	Wait();
	Saver::Wait();

	LOCK lock(cs);
	isLoading = true;
	
	if (isAsync)
	{
		hEvent.NonSignal();
		hThread = _beginthreadex(nullptr, 0u, Loading, nullptr, 0u, nullptr);
		if (hThread == 0)
		{
			isAsync = false;
			Loading(nullptr);
		}
	}
	else
		Loading(nullptr);
}

int Loader::GetInt(const std::string& _key)
{
	if (Wait())
	{
		std::unordered_map<std::string, std::string>::iterator it = info.find(_key);
		if (it != info.end())
			return *reinterpret_cast<int*>(&it->second[0]);
	}
	return 0;
}

float Loader::GetFloat(const std::string& _key)
{
	int data = GetInt(_key);
	return *reinterpret_cast<float*>(&data);
}

std::string Loader::GetString(const std::string& _key)
{
	if (Wait())
	{
		std::unordered_map<std::string, std::string>::iterator it = info.find(_key);
		if (it != info.end())
			return it->second;
	}
	return "";
}

bool Loader::IsLoading()
{
	LOCK lock(cs);
	return isLoading;
}

bool Loader::Wait()
{
	LOCK lock(cs);
	if (isLoading)
		return WaitForSingleObject(hEvent.handle, INFINITE) == WAIT_OBJECT_0;
	return true;
}

unsigned Loader::Loading(LPVOID _param)
{
	std::string data;

	std::ifstream load("Save\\save.ur", std::ifstream::binary);

	if (load.is_open())
	{
		//ファイルサイズ
		load.seekg(0, std::ifstream::end);

		unsigned size = static_cast<unsigned>(load.tellg());

		if (size > check_size)
		{
			load.seekg(0, std::ifstream::beg);

			//読み込み
			std::vector<char> buf;
			buf.resize(size);

			load.read(&buf[0], size);

			load.close();

			//データ数
			size = static_cast<unsigned>(check.size());

			unsigned count = *reinterpret_cast<int*>(&buf[size]);

			size += INT_SIZE;

			//データ取得
			for (unsigned i = 0u; i < count; ++i)
			{
				//キーの長さ
				unsigned keyLength = *reinterpret_cast<unsigned*>(&buf[size]);
				size += INT_SIZE;

				//キー
				std::string key;
				key.assign(&buf[size], keyLength);
				size += keyLength;

				//データ長さ
				unsigned dataLength = *reinterpret_cast<unsigned*>(&buf[size]);
				size += INT_SIZE;

				//データ
				info[key].assign(&buf[size], dataLength);
				size += dataLength;
			}
		}
	}

	LOCK lock(cs);
	isLoading = false;

	hEvent.Signal();

	return 1u;
}
