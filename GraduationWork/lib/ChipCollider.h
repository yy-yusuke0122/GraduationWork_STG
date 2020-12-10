#pragma once

#include "Component.h"

class MapChip;

class Chip;

class ChipCollider :public Component
{
	struct CollisionState
	{
		CollisionState() :
			chip(nullptr), isCollide(false) {}
		Chip* chip;
		bool isCollide;
	};

public:
	ChipCollider() :
		map(nullptr), sizeX(1), sizeY(1)
	{
	}

	~ChipCollider();

	void Update()override;

	bool CheckCollide(Chip* _chip);

	void ClearChip();

	void AddChip(Chip* _chip);

public:
	MapChip* map;

	CollisionState hitChip[4];

	int sizeX, sizeY;

private:

};
