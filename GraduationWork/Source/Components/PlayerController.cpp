#include "PlayerController.h"
#include "TestPlayerState.h"
#include "TestPlayerIdle.h"
#include "TestPlayerMove.h"
#include "TestPlayerAttack.h"

PlayerController::PlayerController() :
	currentState(""), stateComp(nullptr)
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::Start()
{
	state = AddComponent<StateController>();
	state->SetStateManager<TestPlayerState>();

	AddComponent<TestPlayerIdle>()->SetActive(false);
	AddComponent<TestPlayerMove>()->SetActive(false);
	AddComponent<TestPlayerAttack>()->SetActive(false);
}

void PlayerController::Update()
{
	if (currentState != state->GetState()) {
		currentState = state->GetState();

		if (stateComp != nullptr)
			stateComp->SetActive(false);

		if (currentState == "Idle") stateComp = GetComponent<TestPlayerIdle>();
		else if (currentState == "Move") stateComp = GetComponent<TestPlayerMove>();
		else if (currentState == "Attack") stateComp = GetComponent<TestPlayerAttack>();

		stateComp->SetActive(true);
	}

	printfDx("%s\n", state->GetState().c_str());
	printfDx("px : %f\n", transform->position.x);
	printfDx("py : %f\n", transform->position.y);

	// 着地確認
	CheckLanding();
}

void PlayerController::CheckLanding()
{
	//if (jumpComponent->IsLanding())
	//	return;

	//ImageRenderer* p = GetComponent<ImageRenderer>();
	//int size = p->GetSizeY();	// 画像の縦幅
	//float h = Stage::GetY();	// ステージの高さ
	//float foot = transform->position.y + size / 2;

	//if (foot > h) {
	//	jumpComponent->Land();

	//	VECTOR3 pos = transform->position;
	//	pos.y = h - size / 2;
	//	transform->SetPosition(pos);
	//}
}
