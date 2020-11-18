#include "PlayerRotate.h"

PlayerRotate::PlayerRotate() :
	imageRenderer(nullptr)
{
}

PlayerRotate::~PlayerRotate()
{
}

void PlayerRotate::Start()
{
	imageRenderer = GetComponent<ImageRenderer>();
}

void PlayerRotate::Update()
{
	imageRenderer->rotation += 1.0f;
}

void PlayerRotate::SetRotate(float _angle)
{
	imageRenderer->rotation = _angle;
}
