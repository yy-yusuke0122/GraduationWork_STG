#pragma once
#include "Character.h"

class PlayerController;

class Player : public Character {
public:
	Player();
	~Player();
	void Start();
private:
	PlayerController* playerController;

};