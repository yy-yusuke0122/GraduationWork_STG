#include "TestPlayerManager.h"
#include "TestPlayerState.h"
#include "TestPlayerIdle.h"
#include "TestPlayerMove.h"
#include "TestPlayerAttack.h"
#include "../Components/Jump.h"
#include "../Objects/Stage.h"

TestPlayerManager::TestPlayerManager() :
	currentState(""), faceDir(VECTOR3::right()),
	state(nullptr), stateComp(nullptr), physics(nullptr), jumpComp(nullptr), renderer(nullptr)
{
}

TestPlayerManager::~TestPlayerManager()
{
}

void TestPlayerManager::Start()
{
	state = AddComponent<StateController>();
	state->SetStateManager<TestPlayerState>();
	jumpComp = AddComponent<JumpComponent>();
	physics = GetComponent<PhysicalBehavior>();
	renderer = GetComponent<ImageRenderer>();
}

void TestPlayerManager::Update()
{
	if (currentState != state->GetState()) {
		currentState = state->GetState();

		if (stateComp != nullptr)
			stateComp->Destroy();

		if (currentState == "Idle") stateComp = AddComponent<TestPlayerIdle>();
		else if (currentState == "Move") stateComp = AddComponent<TestPlayerMove>();
		else if (currentState == "Attack") stateComp = AddComponent<TestPlayerAttack>();
	}

	printfDx("%s\n", state->GetState().c_str());
	printfDx("px : %f\n", transform->position.x);
	printfDx("py : %f\n", transform->position.y);

	// 着地確認
	CheckLanding();
}

void TestPlayerManager::FaceLeft()
{
	faceDir = -VECTOR3::right();
	renderer->turnXFlag = true;
}

void TestPlayerManager::FaceRight()
{
	faceDir = VECTOR3::right();
	renderer->turnXFlag = false;
}

VECTOR3 TestPlayerManager::GetFaceDir() const
{
	return faceDir;
}

void TestPlayerManager::CheckLanding()
{
	if (jumpComp->IsLanding())
		return;

	int size = renderer->GetSizeY();	// 画像の縦幅
	float h = Stage::GetY();	// ステージの高さ
	float foot = transform->position.y + size / 2;

	if (foot > h) {
		jumpComp->Land();

		VECTOR3 pos = transform->position;
		pos.y = h - size / 2;
		transform->SetPosition(pos);
	}
}
