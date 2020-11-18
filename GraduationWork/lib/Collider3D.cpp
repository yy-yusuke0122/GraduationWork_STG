#include "Collider3D.h"
#include "CollideManager.h"
#include "Transform.h"
#include "Function.h"

Collider3D::Collider3D()
{
	CollideManager::Get()->PushCollider3D(this);
}

Collider3D::~Collider3D()
{
	CollideManager::Get()->RemoveCollider3D(this);
}

void Collider3D::ExecuteAllCollisionEnter(Collider3D* _collider)
{
	std::list<Component*> obj_1 = GetComponentAll();
	std::list<Component*> obj_2 = GetComponentAll();
	for (auto it : obj_1) {
		it->OnCollisionEnter(_collider);
	}
	for (auto it : obj_2) {
		it->OnCollisionEnter(_collider);
	}
}

void Collider3D::ExecuteAllCollisionStay(Collider3D* _collider)
{
	std::list<Component*> obj_1 = GetComponentAll();
	std::list<Component*> obj_2 = GetComponentAll();
	for (auto it : obj_1) {
		it->OnCollisionStay(_collider);
	}
	for (auto it : obj_2) {
		it->OnCollisionStay(_collider);
	}
}

void Collider3D::ExecuteAllCollisionExit(Collider3D* _collider)
{
	std::list<Component*> obj_1 = GetComponentAll();
	std::list<Component*> obj_2 = GetComponentAll();
	for (auto it : obj_1) {
		it->OnCollisionExit(_collider);
	}
	for (auto it : obj_2) {
		it->OnCollisionExit(_collider);
	}
}

VECTOR3 Collider3D::GetLocalPosition()
{
	return position;
}

VECTOR3 Collider3D::GetWorldPosition()
{
	return transform->position + position;
}

void Collider3D::SetPosition(VECTOR3 _pos)
{
	position = _pos;
}
