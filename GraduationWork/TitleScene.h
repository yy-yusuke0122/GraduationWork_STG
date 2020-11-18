#pragma once
#include "lib/UrLib.h"

class TitleScene : public Scene {
public:
	TitleScene();
	~TitleScene();
	void Start();
	void Update();

private:
	GameObject* player1;
	GameObject* player2;
	GameObject* player3;
	GameObject* player4;
};