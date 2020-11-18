#include "Component.h"

Component::Component() :
	transform(nullptr), gameObject(nullptr)
{
}

Component::~Component()
{
}

void Component::Start()
{
}

void Component::Update()
{
}

std::list<Component*> Component::GetComponentAll()
{
	return gameObject->GetComponentAll();
}

Scene* Component::GetScene() const
{
	return gameObject->GetScene();
}
