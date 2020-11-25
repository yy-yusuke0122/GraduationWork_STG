#pragma once
#include "../../lib/UrLib.h"

class CharaStateManager : public Component {
public:
	CharaStateManager();
	~CharaStateManager();
	void Start();
	void Update();

	void ChangeState(std::string _nextState);

private:
	Component* state;
	std::string currentName;
	std::string nextName;
};