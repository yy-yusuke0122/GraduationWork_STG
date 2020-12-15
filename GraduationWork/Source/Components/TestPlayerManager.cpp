#include "TestPlayerManager.h"
#include "TestPlayerState.h"
#include "TestPlayerIdle.h"
#include "TestPlayerMove.h"
#include "TestPlayerAttack.h"
#include "../Components/Jump.h"
#include "../Objects/Stage.h"

TestPlayerManager::TestPlayerManager() :
	faceDir(VECTOR3::right()),
	physics(nullptr), jumpComp(nullptr), renderer(nullptr)
{
	state = new ComponentSwitcher();
}

TestPlayerManager::~TestPlayerManager()
{
	delete state;
}

void TestPlayerManager::Start()
{
	state->SetStateMachine<TestPlayerState>();
	state->SetComponent("Idle", AddComponent<TestPlayerIdle>());
	state->SetComponent("Move", AddComponent<TestPlayerMove>());
	state->SetComponent("Attack", AddComponent<TestPlayerAttack>());

	jumpComp = AddComponent<JumpComponent>();
	physics = GetComponent<PhysicalBehavior>();
	renderer = GetComponent<ImageRenderer>();
}

void TestPlayerManager::Update()
{
	state->Update();

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

ComponentSwitcher* TestPlayerManager::GetStateController()
{
	return state;
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
