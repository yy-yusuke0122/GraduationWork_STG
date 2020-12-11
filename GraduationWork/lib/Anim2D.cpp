#include "Anim2D.h"
#include "UrLib.h"

void Anim2D::Update()
{
	// 画像がセットされていなければ終了
	if (handle < 0)
		return;

	// カウントアップ
	time += Time::DeltaTime() * speed;
	if (time > 1.0f) {
		time = 0.0f;
		++currentNum;
	}

	// ループさせる
	if (currentNum > end) {
		currentNum = start;
	}
}

bool Anim2D::IsEndAnim() const
{
	return currentNum == end;
}
