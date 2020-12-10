#include "StateController.h"

StateController::StateController()
{
    state = new StateManager();
}

StateController::~StateController()
{
    delete state;
}

void StateController::Update()
{
    state->Update();
}

std::string StateController::GetState() const
{
    return state->GetState();
}

bool StateController::GetBool(const std::string& _boolName)
{
    return state->GetBool(_boolName);
}

bool StateController::SetBool(const std::string& _boolName, bool _bool)
{
    return state->SetBool(_boolName, _bool);
}
