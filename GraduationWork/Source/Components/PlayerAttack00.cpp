#include "PlayerAttack00.h"
#include "Life.h"
#include "../Objects/SoundManager.h"

PlayerAttack00::PlayerAttack00()
{
}

PlayerAttack00::~PlayerAttack00()
{
}

void PlayerAttack00::Start()
{
	power = 1.0f;

	box = AddComponent<BoxCollider2D>();
	box->box.hl.x = 80.0f;
	box->box.hl.y = 80.0f;

	AddComponent<ImageRenderer>()->SetImage("Media/PlayerAttack00.png");

	// ƒqƒbƒg‰¹‚ÌÝ’è
	SoundManager::Get()->Push("Sound/AttackHit.mp3", "AttackHit");

	// 0.25•bŒã‚É”j‰ó
	Delay<GameObject>* p = AddComponent<Delay<GameObject>>();
	p->instance = gameObject;
	p->endTime = 0.3f;
	p->call = &GameObject::Destroy;
}

void PlayerAttack00::Update()
{
	box->Disp();
}

void PlayerAttack00::OnCollisionEnter2D(Collider2D* _collider)
{
	if (_collider->gameObject->tag == "Enemy") {
		_collider->GetComponent<Life>()->Damage(power);
		SoundManager::Get()->Play("AttackHit");
	}
}
