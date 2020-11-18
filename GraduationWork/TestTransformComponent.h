#pragma once
#include "lib/UrLib.h"

class TestTransformComponent : public Component {
public:
	TestTransformComponent();
	~TestTransformComponent();
	void Start();
	void Update();

	void UseControl(bool _use);
private:
	bool isControl;
};