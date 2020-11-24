#pragma once
#include "Character.h"

class PlayerController;

class Player : public Character {
public:
	Player();
	~Player();
	void Start() override;
	void Update() override;
private:
	PlayerController* playerController;
};