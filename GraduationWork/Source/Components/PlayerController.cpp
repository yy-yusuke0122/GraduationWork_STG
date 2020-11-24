#include "PlayerController.h"
#include "PlayerMover.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::Start()
{
	playerMover = AddComponent<PlayerMover>();
}

void PlayerController::Update()
{
	if (Input::IsKeyPush(KEY::KEY_LEFT)) {
		playerMover->Move(false);
	}
	else if (Input::IsKeyPush(KEY::KEY_RIGHT)) {
		playerMover->Move(true);
	}
	if (Input::IsKeyDown(KEY::KEY_SPACE)) {
		playerMover->Jump();
	}
}
