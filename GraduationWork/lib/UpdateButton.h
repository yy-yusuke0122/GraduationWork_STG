#pragma once
#include "UrLib.h"

class UpdateButton : public Component {
public:
	UpdateButton();
	~UpdateButton();
	void Start() override;
	void Update() override;

private:
	Button* button;
};