#include "PlayerAttack00.h"
#include "Life.h"

PlayerAttack00::PlayerAttack00()
{
}

PlayerAttack00::~PlayerAttack00()
{
}

void PlayerAttack00::Start()
{
	power = 1.0f;

	BoxCollider2D* box = AddComponent<BoxCollider2D>();
	box->box.hl.x = 128.0f;
	box->box.hl.y = 128.0f;

	AddComponent<ImageRenderer>()->SetImage("Media/Enemy.png");
}

void PlayerAttack00::OnCollisionEnter2D(Collider2D* _collider)
{
	if (_collider->gameObject->tag == "Player") {
		_collider->GetComponent<Life>()->Damage(power);
	}
}
