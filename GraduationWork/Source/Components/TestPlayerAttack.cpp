#include "TestPlayerAttack.h"
#include "TestPlayerManager.h"
#include "PlayerAttack00.h"
#include "PlayerAttack01.h"
#include "PlayerAttack02.h"

namespace {
	const float ATTACK_COOL = 0.3f;
	const float ATTACK_TIME = 0.8f;
	const float ATTACK_DIF = 30.0f;
}

TestPlayerAttack::TestPlayerAttack() :
	manager(nullptr), state(nullptr),
	attackCount(0), attackTime(0.0f)
{
}

TestPlayerAttack::~TestPlayerAttack()
{
}

void TestPlayerAttack::Start()
{
	manager = GetComponent<TestPlayerManager>();
	state = manager->GetStateController();
	
	Attack();
}

void TestPlayerAttack::Update()
{
	attackTime -= Time::DeltaTime();

	if (attackTime <= 0.0f) {
		state->SetBool("isAttack", false);
	}

	if (Input::IsKeyDown(KEY::KEY_ENTER) && CanAttack()) {
		Attack();
	}

	printfDx("attackCount : %d\n", attackCount);
}

void TestPlayerAttack::Attack()
{
	// 攻撃時間を更新
	attackTime = ATTACK_TIME;

	// 顔の向きを更新
	CheckAxisInput();

	// 攻撃オブジェクトを生成
	GameObject* obj = Instantiate<GameObject>();
	VECTOR3 pos = VECTOR3(transform->position);
	pos += manager->GetFaceDir() * ATTACK_DIF;
	obj->transform->SetPosition(pos);

	// 現在のカウントに対応した攻撃をアタッチ
	switch (attackCount) {
	case 0: obj->AddComponent<PlayerAttack00>(); break;
	case 1: obj->AddComponent<PlayerAttack01>(); break;
	case 2: obj->AddComponent<PlayerAttack02>(); break;
	default: break;
	}

	// 攻撃カウントをインクリメント
	++attackCount;
	if (attackCount > 2) {
		attackCount = 0;
	}
}

bool TestPlayerAttack::CanAttack()
{
	float time = ATTACK_TIME - attackTime;
	return time > ATTACK_COOL;
}

void TestPlayerAttack::CheckAxisInput()
{
	if (!Input::IsKeyNone(KEY::KEY_LEFT)) {
		manager->FaceLeft();
	}
	else if (!Input::IsKeyNone(KEY::KEY_RIGHT)) {
		manager->FaceRight();
	}
}
