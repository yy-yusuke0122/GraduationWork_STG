#include "Scene.h"
#include "Object.h"

Object::Object() :
    className(""), active(true), isDestroy(false)
{
}

Object::~Object()
{
}

void Object::Start()
{
}

void Object::Update()
{
}

void Object::PostUpdate()
{
}

std::string Object::GetTypeName() const
{
    return className;
}

bool Object::IsActive() const
{
    return active;
}

void Object::SetActive(bool _active)
{
    active = _active;
}

bool Object::IsDestroy() const
{
    return isDestroy;
}

void Object::Destroy()
{
    isDestroy = true;
}

GameObject* Object::FindGameObject(const std::string& _tag)
{
    return GetScene()->FindGameObject(_tag);
}
