#pragma once
#include "lib/UrLib.h"

class Player;

class GameMain :public Scene
{
public:
	GameMain():
		num(0), random(Random::GetF())
	{
	}

	~GameMain()
	{
	}

	void Start()override;

	void Update()override;

private:
	int num;

	Player* player;

	GameObject* child;

	MeshRenderer* mesh;

	void Add();

	float random;
};
