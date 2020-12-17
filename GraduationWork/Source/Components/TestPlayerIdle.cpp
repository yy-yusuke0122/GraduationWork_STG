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
	if (Input::GetAxis().Length() > 0.0f) {
		state->SetBool("isMove", true);
	}
}

void TestPlayerIdle::CheckAttackInput()
{
	if (Input::IsKeyDown(KEY::KEY_ENTER)) {
		state->SetBool("isAttack", true);
	}
}
