#pragma once
#include "../../lib/UrLib.h"

class CharaState : public Component {
public:
	CharaState();
	virtual ~CharaState();

	void ChangeState(std::string _nextState);
};