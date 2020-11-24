#pragma once
#include "Character.h"

class Life;
class PlayerController;

class Player : public GameObject {
public:
	Player();
	~Player();
	void Start();
private:
	ImageRenderer* imageRenderer;
	Life* life;
	Animator2D* animator2D;
	PlayerController* playerController;

};