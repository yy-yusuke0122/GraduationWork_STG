#pragma once
#include "Character.h"

class TestPlayerManager;
class TestPlayerState;

class Player : public Character {
public:
	Player();
	~Player();
	void Start();

private:
	TestPlayerManager* playerController;
};