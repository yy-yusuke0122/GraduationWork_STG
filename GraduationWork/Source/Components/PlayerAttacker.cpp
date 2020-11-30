#include "PlayerAttacker.h"
#include "../Objects/NullObject.h"
#include "PlayerAttack00.h"
#include "PlayerAttack01.h"
#include "PlayerAttack02.h"

namespace {
	const float ATTACK_DIF = 40.0f;
}

PlayerAttacker::PlayerAttacker()
{
}

PlayerAttacker::~PlayerAttacker()
{
}

void PlayerAttacker::Start()
{
	attackCount = 0;
}

void PlayerAttacker::Update()
{
	printfDx("attackCount : %d\n", attackCount);
}

void PlayerAttacker::Attack(VECTOR2 _faceDir)
{
	// 攻撃オブジェクトを生成
	GameObject* obj = Instantiate<GameObject>();
	VECTOR3 pos = VECTOR3(transform->position);
	pos += _faceDir * ATTACK_DIF;
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
