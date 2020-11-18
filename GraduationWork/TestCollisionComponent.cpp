#include "TestCollisionComponent.h"

void TestCollisionComponent::Start()
{
}

void TestCollisionComponent::Update()
{
}

void TestCollisionComponent::OnCollisionEnter2D(Collider2D* _collider)
{
}

void TestCollisionComponent::OnCollisionStay2D(Collider2D* _collider)
{
	printfDx("Hit!!");
}
