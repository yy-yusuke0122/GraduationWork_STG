#include "PlayerAttacker.h"
#include "../Objects/NullObject.h"
#include "PlayerAttack00.h"

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
}

void PlayerAttacker::Update()
{
}

void PlayerAttacker::Attack(VECTOR2 _faceDir)
{
	GameObject* obj = Instantiate<NullObject>();
	VECTOR3 pos = VECTOR3(transform->position);
	pos += _faceDir * ATTACK_DIF;
	obj->transform->SetPosition(pos);
	obj->AddComponent<PlayerAttack00>();
}
