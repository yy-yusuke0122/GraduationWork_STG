#include "SoundManager.h"

SoundManager* SoundManager::instance = nullptr;

SoundManager* SoundManager::Create(Scene* _parent)
{
	if (instance == nullptr)
		instance = _parent->Instantiate<SoundManager>();
	return Get();
}

SoundManager* SoundManager::Get()
{
	return instance;
}

void SoundManager::Start()
{
}

void SoundManager::Push(const std::string& _path, const std::string& _name)
{
	if (sounds.find(_name) == sounds.end())
	{
		GameObject* child = Instantiate<GameObject>();
		child->SetParent(this);

		Sound* s = child->AddComponent<Sound>();

		s->Load(_path);

		sounds[_name] = s;
	}
}

void SoundManager::Play(const std::string& _path)
{
	sounds[_path]->Play();
}
