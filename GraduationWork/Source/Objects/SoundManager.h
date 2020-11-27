#pragma once
#include "../../lib/UrLib.h"

class SoundManager :public GameObject
{
public:
	SoundManager()
	{
		sounds.clear();
	}

	~SoundManager()
	{
	}

public:
	static SoundManager* Create(Scene*_parent);

	static SoundManager* Get();

	static void Destroy() { instance = nullptr; }

	void Start() override;
	void Push(const std::string& _path, const std::string& _name);
	void Play(const std::string& _name);


private:
	struct NODE {
		Sound* s;
		std::string path;
	};
	std::unordered_map<std::string, Sound*> sounds;

	static SoundManager* instance;
};
