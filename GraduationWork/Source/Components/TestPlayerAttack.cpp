#include "TestPlayerAttack.h"
#include "PlayerAttack00.h"
#include "PlayerAttack01.h"
#include "PlayerAttack02.h"

namespace {
	const float ATTACK_TIME = 0.8f;
}

TestPlayerAttack::TestPlayerAttack()
{
}

TestPlayerAttack::~TestPlayerAttack()
{
}

void TestPlayerAttack::Start()
{
	state = GetComponent<StateController>();

	attackCount = 0;
}

void TestPlayerAttack::Update()
{
	attackTime -= Time::DeltaTime();
	if (attackTime <= 0.0f) {
		state->SetBool("isAttack", false);
	}

	if (Input::IsKeyDown(KEY::KEY_ENTER)) {
		Attack();
	}
	printfDx("attackCount : %d\n", attackCount);
}

void TestPlayerAttack::Attack()
{
	attackTime = ATTACK_TIME;

	// �U���I�u�W�F�N�g�𐶐�
	GameObject* obj = Instantiate<GameObject>();
	VECTOR3 pos = VECTOR3(transform->position);
	//pos += _faceDir * ATTACK_DIF;
	obj->transform->SetPosition(pos);

	// ���݂̃J�E���g�ɑΉ������U�����A�^�b�`
	switch (attackCount) {
	case 0: obj->AddComponent<PlayerAttack00>(); break;
	case 1: obj->AddComponent<PlayerAttack01>(); break;
	case 2: obj->AddComponent<PlayerAttack02>(); break;
	default: break;
	}

	// �U���J�E���g���C���N�������g
	++attackCount;
	if (attackCount > 2) {
		attackCount = 0;
	}
}
