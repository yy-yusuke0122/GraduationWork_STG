#pragma once
#include "../../lib/UrLib.h"

class TitleScene : public Scene {
public:
	TitleScene();
	~TitleScene();
	void Start();
	void Update();
private:
	void CheckInput();
};