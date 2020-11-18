#include "AnimTestComp.h"

AnimTestComp::AnimTestComp()
{
}

AnimTestComp::~AnimTestComp()
{
}

void AnimTestComp::Start()
{
	AddAnim(0, 1, "Idle");
	AddAnim(2, 3, "Walk");

	CreateTransDirection("Idle", "Walk");
	CreateTransDirection("Walk", "Idle");

	CreateBool("isWalk");
	AddTransDirInfo("Idle", "Walk", "isWalk", true);
	AddTransDirInfo("Walk", "Idle", "isWalk", false);
}
