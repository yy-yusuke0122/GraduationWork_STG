#include "PlayerAttack02.h"
#include "Life.h"
#include "../Objects/SoundManager.h"

namespace {
	const int COOLTIME = 10;
}

PlayerAttack02::PlayerAttack02()
{
}

PlayerAttack02::~PlayerAttack02()
{
}

void PlayerAttack02::Start()
{
	power = 1.0f;
	coolTime = 0;

	CircleCollider2D* circle = AddComponent<CircleCollider2D>();
	circle->circle.r = 50.0f;
	//box = AddComponent<BoxCollider2D>();
	//box->box.hl.x = 120.0f;
	//box->box.hl.y = 120.0f;

	AddComponent<ImageRenderer>()->SetImage("Media/PlayerAttack02.png");

	// ヒット音の設定
	SoundManager::Get()->Push("Sound/AttackHit.mp3", "AttackHit");

	// 0.25秒後に破壊
	Delay<GameObject>* p = AddComponent<Delay<GameObject>>();
	p->instance = gameObject;
	p->endTime = 1.0f;
	p->call = &GameObject::Destroy;
}

void PlayerAttack02::Update()
{
	/*box->Disp();*/
}

void PlayerAttack02::OnCollisionStay2D(Collider2D* _collider)
{
	// エネミーじゃなければ終了
	if (_collider->gameObject->tag != "Enemy")
		return;

	--coolTime;
	if (coolTime < 0) {
		coolTime = COOLTIME;
		_collider->GetComponent<Life>()->Damage(power);
		SoundManager::Get()->Play("AttackHit");
	}
}
