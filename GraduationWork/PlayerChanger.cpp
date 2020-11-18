#include "PlayerChanger.h"

void PlayerChanger::Start()
{
	count = 0;
	imageRenderer = GetComponent<ImageRenderer>();
}

void PlayerChanger::Update()
{
	if (++count == 120) {
		imageRenderer->SetImage("..\\Media\\testImage2.png");
	}
	else if (count > 240) {
		count = 0;
		imageRenderer->SetImage("..\\Media\\testImage.png");
	}
}
