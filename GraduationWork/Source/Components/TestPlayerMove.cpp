#include "TestPlayerMove.h"

TestPlayerMove::TestPlayerMove() :
	state(nullptr)
{
}

TestPlayerMove::~TestPlayerMove()
{
}

void TestPlayerMove::Start()
{
	state = GetComponent<StateController>();

	speed = 5.0f;
}

void TestPlayerMove::Update()
{
	CheckMoveInput();

	Move();

	if (Input::IsKeyDown(KEY::KEY_ENTER)) {
		state->SetBool("isAttack", true);
	}
}

void TestPlayerMove::CheckMoveInput()
{
	dir.Clear();

	if (!Input::IsKeyNone(KEY::KEY_LEFT)) {
		dir += -VECTOR3::right() * speed * Time::DeltaTime();
	}
	if (!Input::IsKeyNone(KEY::KEY_RIGHT)) {
		dir += VECTOR3::right() * speed * Time::DeltaTime();
	}
	if (!Input::IsKeyNone(KEY::KEY_UP)) {
		dir += -VECTOR3::up() * speed * Time::DeltaTime();
	}
	if (!Input::IsKeyNone(KEY::KEY_DOWN)) {
		dir += VECTOR3::up() * speed * Time::DeltaTime();
	}

	if (dir.Length() == 0.0f) {
		state->SetBool("isMove", false);
	}
}

void TestPlayerMove::Move()
{
	transform->AddPosition(dir);
}
