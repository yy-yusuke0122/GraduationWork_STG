#pragma once

#include "../../lib/UrLib.h"

class LoadingScene :public Scene
{
public:
	LoadingScene()
	{
	}

	~LoadingScene()
	{
	}

	void Start()override;

	void Update()override;

private:

public:
	static float asyncLoadMin;//”ñ“¯ŠúÅ’áŠÔ

};
