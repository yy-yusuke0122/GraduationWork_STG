#include "PlayerComponent.h"

PlayerComponent::PlayerComponent() :
	a(0), num(0u)
{
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::Start()
{
	printfDx("千夏フルパワー！！！\n");
}

void PlayerComponent::Update()
{
	transform->AddPosition(VGet(-1.0f, 0.0f, 0.0f));

	if (Input::IsKeyDown(KEY::KEY_SPACE))
	{
		ImageRenderer* p = GetComponent<ImageRenderer>();
		if (p->GetDrawMaxNumber() == 1)
		{
			p->SetImageDiv(p->GetPath().c_str(), 3, 3, 5);
		}
		else
		{
			p->SetImage(p->GetPath().c_str());
		}
	}

	if (++a > 20)
	{
		ImageRenderer* p = GetComponent<ImageRenderer>();

		if (++num >= p->GetDrawMaxNumber())
			num = 0;
		p->SetImageNumber(num);

		a = 0;
	}

}
