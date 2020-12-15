#include "TestPlayerIdle.h"
#include "TestPlayerManager.h"

TestPlayerIdle::TestPlayerIdle() :
	manager(nullptr), state(nullptr)
{
}

TestPlayerIdle::~TestPlayerIdle()
{
}

void TestPlayerIdle::Start()
{
	manager = GetComponent<TestPlayerManager>();
	state = manager->GetStateController();
}

void TestPlayerIdle::Update()
{
	CheckMoveInput();
	CheckAttackInput();
}

void TestPlayerIdle::CheckMoveInput()
{
	if (Input::IsKeyPush(KEY::KEY_LEFT)) {
		state->SetBool("isMove", true);
	}
	else if (Input::IsKeyPush(KEY::KEY_RIGHT)) {
		state->SetBool("isMove", true);
	}
	else if (Input::IsKeyPush(KEY::KEY_UP)) {
		state->SetBool("isMove", true);
	}
	else if (Input::IsKeyPush(KEY::KEY_DOWN)) {
		state->SetBool("isMove", true);
	}
}

void TestPlayerIdle::CheckAttackInput()
{
	if (Input::IsKeyDown(KEY::KEY_ENTER)) {
		state->SetBool("isAttack", true);
	}
}
