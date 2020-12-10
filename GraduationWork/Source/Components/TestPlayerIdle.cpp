#include "TestPlayerIdle.h"

TestPlayerIdle::TestPlayerIdle()
{
}

TestPlayerIdle::~TestPlayerIdle()
{
}

void TestPlayerIdle::Start()
{
	state = GetComponent<StateController>();
}

void TestPlayerIdle::Update()
{
	CheckMoveInput();
	CheckAttackInput();

	transform->AddPosition(VECTOR3::right() * 3.0f);
}

void TestPlayerIdle::CheckMoveInput()
{
	if (Input::IsKeyDown(KEY::KEY_LEFT)) {
		state->SetBool("isMove", true);
	}
	else if (Input::IsKeyDown(KEY::KEY_RIGHT)) {
		state->SetBool("isMove", true);
	}
	else if (Input::IsKeyDown(KEY::KEY_UP)) {
		state->SetBool("isMove", true);
	}
	else if (Input::IsKeyDown(KEY::KEY_DOWN)) {
		state->SetBool("isMove", true);
	}
}

void TestPlayerIdle::CheckAttackInput()
{
	if (Input::IsKeyDown(KEY::KEY_ENTER)) {
		state->SetBool("isAttack", true);
	}
}
