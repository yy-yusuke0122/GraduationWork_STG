#include "UpdateButton.h"

UpdateButton::UpdateButton() :
	button(nullptr)
{
}

UpdateButton::~UpdateButton()
{
}

void UpdateButton::Start()
{
	button = dynamic_cast<Button*>(gameObject);
}

void UpdateButton::Update()
{
	VECTOR2 pos;
	pos.x = transform->position.x;
	pos.y = transform->position.y;
	button->textObj->Draw(pos);
}
