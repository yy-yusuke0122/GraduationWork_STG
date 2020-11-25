#include "PlayerAttacker.h"
#include "../Objects/NullObject.h"
#include "PlayerAttack00.h"

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

void PlayerAttacker::Attack()
{
	GameObject* obj = Instantiate<NullObject>();
	obj->transform->SetPosition(transform->position);
	obj->AddComponent<PlayerAttack00>();
}
