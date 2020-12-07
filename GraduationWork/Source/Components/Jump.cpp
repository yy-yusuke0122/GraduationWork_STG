#include "Jump.h"
#include "../../lib/PhysicalBehavior.h"

JumpComponent::JumpComponent() :
	jumpPower(1.0f), jumpCount(0), maxJumpCount(1),
	jumpDir(-VECTOR3::up()), physics(nullptr)
{
}

void JumpComponent::SetJumpDir(VECTOR3 _dir)
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
	physics = AddComponent<PhysicalBehavior>();
}

void JumpComponent::Update()
{
	printfDx("jumpCount %d / %d\n", jumpCount, maxJumpCount);
}

void JumpComponent::Jump(bool _velocityChange)
{
	// Å‘åƒWƒƒƒ“ƒv‰ñ”ˆÈã‚È‚çI—¹
	if (jumpCount >= maxJumpCount)
		return;

	++jumpCount;

	if (_velocityChange) {
		physics->velocity = jumpDir * jumpPower;
	}
	else {
		physics->velocity += jumpDir * jumpPower;
	}
	
	physics->isLanding = false;
}

void JumpComponent::Land()
{
	jumpCount = 0;
	physics->velocity.y = 0.0f;
	physics->isLanding = true;
}

bool JumpComponent::IsLanding() const
{
	return physics->isLanding;
}
