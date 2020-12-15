#pragma once
#include "dxlib/DxLib.h"
#include "typedef.h"
#include "Function.h"
#include "SceneManager.h"
#include "Transform.h"
#include "ImageRenderer.h"
#include "ComponentSwitcher.h"
#include "Animator2D.h"
#include "Input.h"
#include "Time.h"
#include "Delay.h"
#include "Sound.h"
#include "SoundListener.h"
#include "CircleCollider2D.h"
#include "BoxCollider2D.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "MeshRenderer.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Saver.h"
#include "Loader.h"
#include "Random.h"
#include "Debug.h"
#include "Scroll.h"
#include "MapChip.h"
#include "Chip.h"
#include "PhysicalBehavior.h"

namespace UrLib {
	int Init(int ScreenSizeX, int ScreenSizeY, int ColorBitDepth, int WindowMode, bool IsShadowCalc = true);
	void Update();
	int Draw();
	int End();

	class Screen {
	public:
		static int x, y;
	};

	struct Meter
	{
		static float oneMeter;
	};
}
using namespace UrLib;