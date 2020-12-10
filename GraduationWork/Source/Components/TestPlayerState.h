#pragma once
#include "../../lib/UrLib.h"

class TestPlayerState : public StateManager {
public:
	TestPlayerState();
	~TestPlayerState();
	void Start() override;
};