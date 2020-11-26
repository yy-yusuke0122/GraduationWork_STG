#include "Collider2D.h"
#include "CollideManager.h"
#include "typedef.h"
#include "Function.h"
#include "Transform.h"

Collider2D::Collider2D()
{
	CollideManager::Get()->PushCollider2D(this);
}

Collider2D::~Collider2D()
{
	CollideManager::Get()->RemoveCollider2D(this);
}

void Collider2D::ExecuteAllCollisionEnter(Collider2D* _collider)
{
	std::list<Component*> obj_1 = GetComponentAll();
	for (auto it : obj_1) {
		it->OnCollisionEnter2D(_collider);
	}
}

void Collider2D::ExecuteAllCollisionStay(Collider2D* _collider)
{
	std::list<Component*> obj_1 = GetComponentAll();
	for (auto it : obj_1) {
		it->OnCollisionStay2D(_collider);
	}
}

void Collider2D::ExecuteAllCollisionExit(Collider2D* _collider)
{
	std::list<Component*> obj_1 = GetComponentAll();
	for (auto it : obj_1) {
		it->OnCollisionExit2D(_collider);
	}
}
