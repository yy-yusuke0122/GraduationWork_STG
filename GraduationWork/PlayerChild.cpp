#include "PlayerChild.h"
#include "PlayerComponent.h"
#include "Player.h"

PlayerChild::PlayerChild()
{
}

PlayerChild::~PlayerChild()
{
}

void PlayerChild::Start() 
{
	AddComponent<PlayerComponent>();
}