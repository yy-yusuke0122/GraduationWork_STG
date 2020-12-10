#pragma once
#include "../../lib/UrLib.h"

class TestTitleScene : public Scene {
public:
	TestTitleScene();
	~TestTitleScene();
	void Start();
	void Update();
private:
	void CheckInput();

	MapChip* map;
	ImageRenderer* img;
	GameObject* empty;
};