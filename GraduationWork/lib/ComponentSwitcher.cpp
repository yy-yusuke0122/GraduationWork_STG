#include "ComponentSwitcher.h"
#include "Component.h"

ComponentSwitcher::ComponentSwitcher() :
    state(nullptr), currentComp(nullptr), currentState("")
{
    components.clear();
}

ComponentSwitcher::~ComponentSwitcher()
{
    if (state != nullptr)
        delete state;
}

void ComponentSwitcher::Update()
{
    if (state != nullptr && currentState != "") {
        state->Update();

        if (currentState != state->GetState()) {
            ChangeStateComp();
        }
    }
}

std::string ComponentSwitcher::GetState() const
{
    return state->GetState();
}

bool ComponentSwitcher::GetBool(const std::string& _boolName)
{
    return state->GetBool(_boolName);
}

bool ComponentSwitcher::SetBool(const std::string& _boolName, bool _bool)
{
    return state->SetBool(_boolName, _bool);
}

bool ComponentSwitcher::SetComponent(const std::string& _stateName, Component* _comp)
{
    Component** comp = FindStateComp(_stateName);
    if (comp != nullptr && _comp != nullptr) {
        *comp = _comp;
        if (currentState == _stateName) {
            (*comp)->SetActive(true);
            currentComp = *comp;
        }
        else (*comp)->SetActive(false);
        return true;
    }

    return false;
}

Component** ComponentSwitcher::FindStateComp(const std::string& _name)
{
    std::map<std::string, Component*>::iterator it = components.find(_name);
    if (it == components.end())
        return nullptr;
    
    return &((*it).second);
}

void ComponentSwitcher::ChangeStateComp()
{
    currentState = state->GetState();

    if (currentComp != nullptr)
        currentComp->SetActive(false);
    
    currentComp = components.find(currentState)->second;

    if (currentComp != nullptr) {
        currentComp->SetActive(true);
        currentComp->Start();
    }
}
