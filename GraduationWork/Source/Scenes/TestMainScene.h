#pragma once
#include "../../lib/UrLib.h"

class Player;
class Enemy;

class TestMainScene : public Scene {
public:
	TestMainScene();
	~TestMainScene();
	void Start();
	void Update();
	void AsyncEnd()override;
private:
	void CheckInput();
private:
	Player* player;
	Enemy* enemy;
};