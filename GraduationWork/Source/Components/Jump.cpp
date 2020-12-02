#include "Jump.h"

JumpComponent::JumpComponent() :
	jumpPower(1.0f), jumpCount(0), maxJumpCount(1),
	jumpDir(-VECTOR2::up()), localGravity(VECTOR2::up() * 9.8f), fallVec(VECTOR2::zero()), isLanding(false)
{
}

void JumpComponent::SetJumpDir(VECTOR2 _dir)
{
	if (_dir.Length() > 1.0f) {
		_dir.Norm();
	}

	jumpDir = _dir;
}

JumpComponent::~JumpComponent()
{
}

void JumpComponent::Start()
{
}

void JumpComponent::Update()
{
	if (!isLanding) {
		fallVec += localGravity * Time::DeltaTime();
		transform->AddPosition(fallVec);
	}
	printfDx("jumpCount %d / %d\n", jumpCount, maxJumpCount);
}

void JumpComponent::Jump() 
{
	if (jumpCount < maxJumpCount) {
		++jumpCount;
		fallVec = jumpDir * jumpPower;
	}
}
