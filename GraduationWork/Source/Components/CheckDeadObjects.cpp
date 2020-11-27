#include "Life.h"
#include "../Objects/Character.h"
#include "CheckDeadObjects.h"

void CheckDeadObjects::Start()
{
	lifeList.emplace_back(GetScene()->FindGameObject("Player")->GetComponent<Life>());
	lifeList.emplace_back(GetScene()->FindGameObject("Enemy")->GetComponent<Life>());
}

void CheckDeadObjects::Update()
{
	for (std::list<Life*>::iterator it = lifeList.begin(), end = lifeList.end(); it != end;)
	{
		if ((*it)->hp <= 0.f)
		{
			reinterpret_cast<Character*>((*it)->gameObject)->Dead();
			it = lifeList.erase(it);
		}
		else
		{
			++it;
		}
	}

}
