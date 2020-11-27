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
	faceDir = VECTOR2(1.0f, 0.0f);
}

void PlayerController::Update()
{
	if (Input::IsKeyPush(KEY::KEY_LEFT)) {
		mover->Move(false);
		faceDir = VECTOR2(-1.0f, 0.0f);
	}
	else if (Input::IsKeyPush(KEY::KEY_RIGHT)) {
		mover->Move(true);
		faceDir = VECTOR2(1.0f, 0.0f);
	}
	if (Input::IsKeyDown(KEY::KEY_UP)) {
		mover->Jump();
	}

	if (Input::IsKeyDown(KEY::KEY_ENTER)) {
		attacker->Attack(faceDir);
	}
}
