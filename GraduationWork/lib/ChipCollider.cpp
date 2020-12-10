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
		if (hitChip[i].chip != _chip)continue;//�`�b�v���Ⴄ�ꍇ�͖���

		//���������ꍇ�AStay���Ă�
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
		if (hitChip[i].chip == nullptr)continue;//�`�b�v���Ȃ��ꍇ�͖���

		if (hitChip[i].isCollide)continue;//�������Ă���`�b�v�͖���

		//�������Ă��Ȃ����Exit���Ă�ŁA�z�񂩂�폜
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
		if (hitChip[i].chip != nullptr)continue;//���ɔz��ɑ��݂���ꍇ�͖���
	
		//Enter���ĂсA�z��ɓo�^
		hitChip[i].chip = _chip;
		for (Component* p : gameObject->GetComponentAll())
			p->OnChipEnter(hitChip[i].chip);
		for (Component* p : _chip->GetComponentAll())
			p->OnChipEnter(gameObject);

		break;
	}
}
