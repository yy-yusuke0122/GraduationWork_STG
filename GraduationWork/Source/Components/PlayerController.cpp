#include "PlayerController.h"
#include "PlayerMover.h"
#include "PlayerAttacker.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::Start()
{
	mover = AddComponent<PlayerMover>();
	attacker = AddComponent<PlayerAttacker>();
}

void PlayerController::Update()
{
	if (Input::IsKeyPush(KEY::KEY_LEFT)) {
		mover->Move(false);
	}
	else if (Input::IsKeyPush(KEY::KEY_RIGHT)) {
		mover->Move(true);
	}
	if (Input::IsKeyDown(KEY::KEY_UP)) {
		mover->Jump();
	}

	if (Input::IsKeyDown(KEY::KEY_ENTER)) {
		attacker->Attack();
	}
}
