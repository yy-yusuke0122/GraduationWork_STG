#include "TestTransformComponent.h"

TestTransformComponent::TestTransformComponent() :
	isControl(false)
{
}

TestTransformComponent::~TestTransformComponent()
{
}

void TestTransformComponent::Start()
{
}

void TestTransformComponent::Update()
{
	if (isControl) {
		if (Input::IsKeyPush(KEY::KEY_LEFT))	transform->AddPosition(VGet(-2.0f, 0.0f, 0.0f));
		if (Input::IsKeyPush(KEY::KEY_RIGHT))	transform->AddPosition(VGet(2.0f, 0.0f, 0.0f));
		if (Input::IsKeyPush(KEY::KEY_UP))		transform->AddPosition(VGet(0.0f, -2.0f, 0.0f));
		if (Input::IsKeyPush(KEY::KEY_DOWN))	transform->AddPosition(VGet(0.0f, 2.0f, 0.0f));
	}
	
	if (Input::IsKeyPush(KEY::KEY_X))		transform->AxisRotateX(2.0f);
	if (Input::IsKeyPush(KEY::KEY_Y))		transform->AxisRotateY(2.0f);
	if (Input::IsKeyPush(KEY::KEY_Z))		transform->AxisRotateZ(2.0f);
	if (Input::IsKeyPush(KEY::KEY_F))		transform->Rotate(transform->GetForward(), 2.0f);
	if (Input::IsKeyPush(KEY::KEY_R))		transform->Rotate(transform->GetRight(), 2.0f);
	if (Input::IsKeyPush(KEY::KEY_U))		transform->Rotate(transform->GetUp(), 2.0f);

	printfDx("pos.x = %f\n", transform->position.x);
	printfDx("pos.y = %f\n", transform->position.y);
	printfDx("pos.z = %f\n", transform->position.z);

	float length = 80.0f;
	DrawLine(
		transform->position.x, transform->position.y, 
		transform->position.x + transform->GetRight().x * length, transform->position.y + transform->GetRight().y * length, 
		GetColor(255, 0, 0)
	);
	DrawLine(
		transform->position.x, transform->position.y,
		transform->position.x + transform->GetUp().x * length, transform->position.y + transform->GetUp().y * length,
		GetColor(0, 255, 0)
	);
	DrawLine(
		transform->position.x, transform->position.y,
		transform->position.x + transform->GetForward().x * length, transform->position.y + transform->GetForward().y * length,
		GetColor(0, 0, 255)
	);
}

void TestTransformComponent::UseControl(bool _use)
{
	isControl = _use;
}
