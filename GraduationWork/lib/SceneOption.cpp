#include "SceneOption.h"

SceneOption::SceneOption() :
	gravityDir(-VECTOR3::up()), gravity(9.8f), useGravity(true),
	friction(0.9f), drag(0.0f)
{
}

SceneOption::~SceneOption()
{
}
