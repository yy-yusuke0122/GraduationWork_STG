#pragma once
#include "lib/UrLib.h"

class PlayerComponent : public Component {
public:
	PlayerComponent();
	~PlayerComponent();
	void Start() override;
	void Update() override;

private:
	int a;
	unsigned num;
};