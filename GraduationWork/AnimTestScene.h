#pragma once
#include "lib/UrLib.h"

class AnimTestComp;

class AnimTestScene : public Scene {
public:
	AnimTestScene();
	~AnimTestScene();
	void Start();
	void Update();
private:
	GameObject* player;
	AnimTestComp* animTestComp;
};