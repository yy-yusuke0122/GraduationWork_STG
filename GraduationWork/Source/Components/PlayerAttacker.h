#pragma once
#include "../../lib/UrLib.h"

class PlayerAttacker : public Component {
public:
	PlayerAttacker();
	~PlayerAttacker();
	void Start();
	void Update();

	void Attack();

private:
};