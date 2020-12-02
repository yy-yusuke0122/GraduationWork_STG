#include "PlayerController.h"
#include "PlayerMover.h"
#include "PlayerAttacker.h"
#include "Jump.h"

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
	jumpComponent = AddComponent<JumpComponent>();
	faceDir = VECTOR2(1.0f, 0.0f);

	jumpComponent->jumpPower = 10.0f;
	jumpComponent->maxJumpCount = 20;
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
		// mover->Jump();
		jumpComponent->Jump();
	}

	if (Input::IsKeyDown(KEY::KEY_L)) {
		jumpComponent->SetJumpDir(-VECTOR2::right());
		jumpComponent->localGravity = VECTOR2::right() * 9.8f;
	}
	if (Input::IsKeyDown(KEY::KEY_R)) {
		jumpComponent->SetJumpDir(VECTOR2::right());
		jumpComponent->localGravity = -VECTOR2::right() * 9.8f;
	}
	if (Input::IsKeyDown(KEY::KEY_D)) {
		jumpComponent->SetJumpDir(-VECTOR2::up());
		jumpComponent->localGravity = VECTOR2::up() * 9.8f;
	}

	if (Input::IsKeyDown(KEY::KEY_ENTER)) {
		attacker->Attack(faceDir);
	}
}
