#pragma once
#include "../../lib/UrLib.h"

class MainScene : public Scene {
public:
	MainScene();
	~MainScene();
	void Start();
	void Update();
private:
	void CheckInput();
};