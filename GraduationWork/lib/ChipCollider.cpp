#include "GameObject.h"
#include "Chip.h"
#include "MapChip.h"
#include "ChipCollider.h"

ChipCollider::~ChipCollider()
{
	if (map != nullptr)
	{
		map->EraseCollider(this);
	}
}

void ChipCollider::Update()
{
	for (CollisionState& r : hitChip)
		r.isCollide = false;
}

bool ChipCollider::CheckCollide(Chip* _chip)
{
	for (int i = 0; i < 4; ++i)
	{
		if (hitChip[i].chip != _chip)continue;//チップが違う場合は無視

		//見つかった場合、Stayを呼ぶ
		hitChip[i].isCollide = true;
		for (Component* p : gameObject->GetComponentAll())
			p->OnChipStay(hitChip[i].chip);
		for (Component* p : hitChip[i].chip->GetComponentAll())
			p->OnChipStay(gameObject);

		return true;
	}
	return false;
}

void ChipCollider::ClearChip()
{
	for (int i = 0; i < 4; ++i)
	{
		if (hitChip[i].chip == nullptr)continue;//チップがない場合は無視

		if (hitChip[i].isCollide)continue;//当たっているチップは無視

		//当たっていなければExitを呼んで、配列から削除
		for (Component* p : gameObject->GetComponentAll())
			p->OnChipExit(hitChip[i].chip);
		for (Component* p : hitChip[i].chip->GetComponentAll())
			p->OnChipExit(gameObject);

		hitChip[i].chip = nullptr;
		hitChip[i].isCollide = false;
	}
}

void ChipCollider::AddChip(Chip* _chip)
{
	for (int i = 0; i < 4; ++i)
	{
		if (hitChip[i].chip != nullptr)continue;//既に配列に存在する場合は無視
	
		//Enterを呼び、配列に登録
		hitChip[i].chip = _chip;
		for (Component* p : gameObject->GetComponentAll())
			p->OnChipEnter(hitChip[i].chip);
		for (Component* p : _chip->GetComponentAll())
			p->OnChipEnter(gameObject);

		break;
	}
}
