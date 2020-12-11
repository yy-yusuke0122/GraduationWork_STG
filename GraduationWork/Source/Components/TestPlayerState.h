#pragma once
#include "../../lib/UrLib.h"

class TestPlayerState : public StateMachine {
public:
	TestPlayerState();
	~TestPlayerState();
	void Start() override;
};