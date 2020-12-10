#include "TestMapColMover.h"

void TMCMover::Update()
{
	if (Input::IsKeyPush(KEY::KEY_RIGHT))
		transform->position.x++;
	if (Input::IsKeyPush(KEY::KEY_LEFT))
		transform->position.x--;
	if (Input::IsKeyPush(KEY::KEY_UP))
		transform->position.y--;
	if (Input::IsKeyPush(KEY::KEY_DOWN))
		transform->position.y++;

	printfDx("enter\n"); PrintInfo(enter);
	printfDx("exit\n"); PrintInfo(exit_);
}

void TMCMover::OnChipEnter(Chip* _c)
{
	int& i = enter.count;
	enter.i[i].h = _c->GetH();
	enter.i[i].w = _c->GetW();
	if (++i >= 4)i = 0;
}

void TMCMover::OnChipStay(Chip* _c)
{
	printfDx("stay	h : %d, w : %d\n", _c->GetH(), _c->GetW());
}

void TMCMover::OnChipExit(Chip* _c)
{
	int& i = exit_.count;
	exit_.i[i].h = _c->GetH();
	exit_.i[i].w = _c->GetW();
	if (++i >= 4)i = 0;
}

void TMCMover::PrintInfo(INFO& _info)
{
	for (int i = 0; i < 4; ++i)
	{
		printfDx("	h : %d, w : %d\n", _info.i[i].h, _info.i[i].w);
	}
}
