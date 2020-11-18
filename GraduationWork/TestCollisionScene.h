#pragma once
#include "lib/UrLib.h"

class TestCollisionScene : public Scene {
public:
	TestCollisionScene();
	~TestCollisionScene();
	void Start();
	void Update();

private:
	GameObject* player1;
	GameObject* player2;
};