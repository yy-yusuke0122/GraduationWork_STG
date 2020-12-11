#include "Anim2D.h"
#include "UrLib.h"

void Anim2D::Update()
{
	// �摜���Z�b�g����Ă��Ȃ���ΏI��
	if (handle < 0)
		return;

	// �J�E���g�A�b�v
	time += Time::DeltaTime() * speed;
	if (time > 1.0f) {
		time = 0.0f;
		++currentNum;
	}

	// ���[�v������
	if (currentNum > end) {
		currentNum = start;
	}
}

bool Anim2D::IsEndAnim() const
{
	return currentNum == end;
}
