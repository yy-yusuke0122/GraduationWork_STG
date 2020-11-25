#include "CharaState.h"
#include "CharaStateManager.h"

CharaState::CharaState()
{
	SetActive(false);
}

CharaState::~CharaState()
{
}

void CharaState::ChangeState(std::string _nextState)
{
	CharaStateManager* manager = GetComponent<CharaStateManager>();

	manager->ChangeState(_nextState);
}
