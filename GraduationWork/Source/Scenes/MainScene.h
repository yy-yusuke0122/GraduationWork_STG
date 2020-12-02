#pragma once
#include "../../lib/UrLib.h"

class Player;
class Enemy;

class MainScene : public Scene {
public:
	MainScene();
	~MainScene();
	void Start();
	void Update();
	void AsyncEnd()override;
private:
	void CheckInput();
private:
	Player* player;
	Enemy* enemy;
};