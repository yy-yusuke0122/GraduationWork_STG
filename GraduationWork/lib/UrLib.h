#pragma once
#include "dxlib/DxLib.h"
#include "typedef.h"
#include "Function.h"
#include "SceneManager.h"
#include "Transform.h"
#include "ImageRenderer.h"
#include "UI.h"
#include "ComponentSwitcher.h"
#include "Animator2D.h"
#include "Anim2D.h"
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
#include "Jump.h"

namespace UrLib {
	int Init(int ScreenSizeX, int ScreenSizeY, bool WindowMode, int ColorBitDepth = 32);
	void Update();
	int Draw();
	int End();

	/// <summary>
	/// コリジョン初期化
	/// </summary>
	/// <param name="Level">4分木空間の分割レベル(下限1、上限15)</param>
	/// <param name="left">当たり判定を行う範囲の左座標</param>
	/// <param name="top">当たり判定を行う範囲の上座標</param>
	/// <param name="right">当たり判定を行う範囲の右座標</param>
	/// <param name="bottom">当たり判定を行う範囲の下座標</param>
	void CollideInit(unsigned int Level = 8, float left = -1000.0f, float top = -1000.0f, float right = 1000.0f, float bottom = 1000.0f);

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