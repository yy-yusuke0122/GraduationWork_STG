#pragma once
#include "lib/UrLib.h"

class TitleSubScene : public Scene {
public:
	TitleSubScene();
	~TitleSubScene();
	void Start();
	void Update();

private:
	int count;
	GameObject* player;
	GameObject* child;
};