#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	AddComponent<ImageRenderer>()->SetImage("../Media/testImage.png");
}
