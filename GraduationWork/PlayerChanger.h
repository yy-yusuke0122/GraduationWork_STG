#pragma once
#include "lib/UrLib.h"

class PlayerChanger : public Component {
public:
	void Start();
	void Update();
private:
	int count;
	ImageRenderer* imageRenderer;
};