#include "CharaStateManager.h"

void CharaStateManager::ChangeState(State _nextState)
{
	if (currentState != _nextState) {
		currentState = _nextState;
	}
}

CharaStateManager::CharaStateManager()
{
}

CharaStateManager::~CharaStateManager()
{
}

void CharaStateManager::Start()
{
}

void CharaStateManager::Update()
{
}

void CharaStateManager::ChangeState(std::string _nextState)
{
}
