#include "PlayerAttack01.h"
#include "Life.h"
#include "../Objects/SoundManager.h"

PlayerAttack01::PlayerAttack01()
{
}

PlayerAttack01::~PlayerAttack01()
{
}

void PlayerAttack01::Start()
{
	power = 2.0f;

	//box = AddComponent<BoxCollider2D>();
	//box->box.hl.x = 100.0f;
	//box->box.hl.y = 60.0f;
	CircleCollider2D* circle = AddComponent<CircleCollider2D>();
	circle->circle.r = 40.0f;

	AddComponent<ImageRenderer>()->SetImage("Media/PlayerAttack01.png");

	// ƒqƒbƒg‰¹‚ÌÝ’è
	SoundManager::Get()->Push("Sound/AttackHit.mp3", "AttackHit");

	// 0.25•bŒã‚É”j‰ó
	Delay<GameObject>* p = AddComponent<Delay<GameObject>>();
	p->instance = gameObject;
	p->endTime = 0.3f;
	p->call = &GameObject::Destroy;
}

void PlayerAttack01::Update()
{
	/*box->Disp();*/
}

void PlayerAttack01::OnCollisionEnter2D(Collider2D* _collider)
{
	if (_collider->gameObject->tag == "Enemy") {
		_collider->GetComponent<Life>()->Damage(power);
		SoundManager::Get()->Play("AttackHit");
	}
}
