#pragma once
#include "lib/UrLib.h"

class PlayerRotate : public Component {
public:
	PlayerRotate();
	~PlayerRotate();
	void Start();
	void Update();

	void SetRotate(float _angle);
private:
	ImageRenderer* imageRenderer;
};