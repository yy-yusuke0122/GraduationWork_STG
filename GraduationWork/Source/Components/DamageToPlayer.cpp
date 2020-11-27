#include "../Components/Life.h"
#include "../Objects/SoundManager.h"
#include "DamageToPlayer.h"

namespace
{
	constexpr float DAMAGE = 1.f;
}

void DamageToPlayer::Start()
{
	SoundManager::Get()->Push("Sound/PlayerDamage.mp3", "PlayerDamage");
}

void DamageToPlayer::Update()
{
}

void DamageToPlayer::OnCollisionEnter2D(Collider2D* _collider)
{
	if (_collider->gameObject->tag == "Player")
	{
		_collider->gameObject->GetComponent<Life>()->Damage(DAMAGE);
		gameObject->Destroy();
		SoundManager::Get()->Play("PlayerDamage");
	}
}
