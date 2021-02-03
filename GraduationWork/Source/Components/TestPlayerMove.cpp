#include "TestPlayerMove.h"
#include "TestPlayerManager.h"

TestPlayerMove::TestPlayerMove() :
	manager(nullptr), state(nullptr), dir(VECTOR2::zero()), speed(0.0f)
{
}

TestPlayerMove::~TestPlayerMove()
{
}

void TestPlayerMove::Start()
{
	manager = GetComponent<TestPlayerManager>();
	state = manager->GetStateController();

	speed = 150.0f;
}

void TestPlayerMove::Update()
{
	CheckMoveInput();

	Move();

	if (Input::IsKeyDown(KEY::KEY_ENTER)) {
		state->SetBool("isAttack", true);
	}
	printfDx("Move‚Å‚·‚æI\n");
}

void TestPlayerMove::CheckMoveInput()
{
	dir.Clear();

	dir = Input::GetAxis() * speed * Time::DeltaTime();
	dir.y *= -1.0f;

	if (dir.Length() == 0.0f) {
		state->SetBool("isMove", false);
	}
}

void TestPlayerMove::Move()
{
	transform->AddPosition(dir);
}
