#pragma once
#include "Character.h"

class Player : public Character {
public:
	Player();
	~Player();
	void Start() override;
	void Update() override;
private:
};