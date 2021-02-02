#include "TestPlayerManager.h"
#include "TestPlayerState.h"
#include "TestPlayerIdle.h"
#include "TestPlayerMove.h"
#include "TestPlayerAttack.h"
#include "../Objects/Stage.h"
#include "../Objects/Player.h"

TestPlayerManager::TestPlayerManager() :
	faceDir(VECTOR3::right()),
	physics(nullptr), jumpComp(nullptr), renderer(nullptr)
{
	state = new ComponentSwitcher();
	stateMachine = new TestPlayerState();
}

TestPlayerManager::~TestPlayerManager()
{
	delete state;
}

void TestPlayerManager::Start()
{
	jumpComp = AddComponent<JumpComponent>();
	physics = GetComponent<PhysicalBehavior>();
	renderer = GetComponent<ImageRenderer>();
	animator = AddComponent<Animator2D>();

	state->SetStateMachine(stateMachine);
	state->SetComponent("Idle", AddComponent<TestPlayerIdle>());
	state->SetComponent("Move", AddComponent<TestPlayerMove>(false));
	state->SetComponent("Attack", AddComponent<TestPlayerAttack>(false));

	animator->SetStateMachine(stateMachine);
	animator->SetAnim("Idle", "Media/Player.png", 2, 2, 4, 1.0f, 0, 3);
	animator->SetAnim("Move", "Media/Enemy.png", 2, 2, 4, 1.0f, 0, 3);
	animator->SetAnim("Attack", "Media/EnemyBullet.png", 2, 2, 4, 1.0f, 0, 3);
}

void TestPlayerManager::Update()
{
	state->Update();
	if (Input::IsKeyDown(KEY::KEY_A)) {
		animator->GetCurrentAnim()->Reverse();
	}

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

TestPlayerState* TestPlayerManager::GetStateMachine()
{
	return nullptr;
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
