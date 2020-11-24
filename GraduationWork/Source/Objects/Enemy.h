#pragma once
#include "Character.h"

class Enemy : public Character {
public:
	Enemy();
	~Enemy();
	void Start() override;
	void Update() override;

private:
	
};