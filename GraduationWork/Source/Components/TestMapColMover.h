#pragma once

#include "../../lib/UrLib.h"

class TMCMover :public Component
{
public:
	struct INFO
	{
		struct INT2 { INT2() :h(-1), w(-1) {} int h, w; };
		INT2 i[4];
		int count;
	};

public:
	TMCMover()
	{
	}

	~TMCMover()
	{
	}

	void Update()override;

	void OnChipEnter(Chip* _c) override;
	void OnChipStay(Chip* _c)override;
	void OnChipExit(Chip* _c)override;

	void PrintInfo(INFO& _info);

private:
	INFO enter, exit_;

};
