#include "PlayerController.h"
#include "PlayerMover.h"
#include "PlayerAttacker.h"
#include "Jump.h"
#include "../Objects/Stage.h"

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
	physics = GetComponent<PhysicalBehavior>();
	faceDir = VECTOR2(1.0f, 0.0f);

	jumpComponent->jumpPower = 20.0f;
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
		physics->gravityDir = -VECTOR3::right();
		jumpComponent->SetJumpDir(VECTOR3::right());
	}
	if (Input::IsKeyDown(KEY::KEY_R)) {
		physics->gravityDir = VECTOR3::right();
		jumpComponent->SetJumpDir(-VECTOR3::right());
	}
	if (Input::IsKeyDown(KEY::KEY_D)) {
		physics->gravityDir = VECTOR3::up();
		jumpComponent->SetJumpDir(-VECTOR3::up());
	}

	if (Input::IsKeyDown(KEY::KEY_ENTER)) {
		attacker->Attack(faceDir);
	}

	// 着地確認
	CheckLanding();
}

void PlayerController::CheckLanding()
{
	if (jumpComponent->IsLanding())
		return;

	ImageRenderer* p = GetComponent<ImageRenderer>();
	int size = p->GetSizeY();	// 画像の縦幅
	float h = Stage::GetY();	// ステージの高さ
	float foot = transform->position.y + size / 2;

	if (foot > h) {
		jumpComponent->Land();

		VECTOR3 pos = transform->position;
		pos.y = h - size / 2;
		transform->SetPosition(pos);
	}
}
