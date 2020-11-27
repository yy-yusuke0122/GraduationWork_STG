#pragma once

#include "../../lib/UrLib.h"

class DamageToPlayer :public Component
{
public:
	DamageToPlayer()
	{
	}

	~DamageToPlayer()
	{
	}

	void Start()override;

	void Update()override;

	void OnCollisionEnter2D(Collider2D* _collider)override;

private:

};
