#include "SoundListener.h"
#include "Function.h"
#include "Transform.h"
#include "Time.h"

void SoundListener::Start()
{
	prevPos = transform->position;
}

void SoundListener::Update()
{
	VECTOR3 velocity = transform->position - prevPos;

	float time = 1.f / Time::DeltaTime();

	Set3DSoundListenerVelocity(velocity * time);//1•b‚Ì‘¬“x

	prevPos = transform->position;

	Set3DSoundListenerPosAndFrontPosAndUpVec(transform->position, transform->GetForward(), transform->GetUp());
}
