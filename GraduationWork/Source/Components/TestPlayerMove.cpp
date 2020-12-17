#include "TestPlayerMove.h"
#include "TestPlayerManager.h"

TestPlayerMove::TestPlayerMove() :
	manager(nullptr), state(nullptr), dir(VECTOR3::zero()), speed(0.0f)
{
}

TestPlayerMove::~TestPlayerMove()
{
}

void TestPlayerMove::Start()
{
	manager = GetComponent<TestPlayerManager>();
	state = manager->GetStateController();

	speed = 20.0f;
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

	VECTOR2 vec = Input::GetAxis() * speed;
	dir.x = vec.x;
	dir.y = vec.y;

	if (dir.Length() == 0.0f) {
		state->SetBool("isMove", false);
	}
}

void TestPlayerMove::Move()
{
	transform->AddPosition(dir);
}
