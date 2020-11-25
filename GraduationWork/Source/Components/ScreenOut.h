#pragma once

#include "../../lib/UrLib.h"

class ScreenOut :public Component
{
public:
	ScreenOut()
	{
	}

	~ScreenOut()
	{
	}

	void OnCollisionExit2D(Collider2D* _collider)override;

private:

};
