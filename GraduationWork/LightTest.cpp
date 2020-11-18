#include "LightTest.h"

void LightTest::Start()
{
	AddComponent<PointLight>()->diffuse = Light::white;
	GetComponent<PointLight>()->specular = Light::white;
	GetComponent<PointLight>()->ambient = Light::black;

	transform->position.x = -100;

	//««‰e««

	//shadow=MakeShadowMap(100, 100);

	//SetShadowMapLightDirection(shadow, VGet(-1.f, -1.f, 1.f));

	//SetShadowMapAdjustDepth(shadow, 0.002f);

	//SetUseShadowMap(0, shadow);

	//SetShadowMapDrawArea(shadow, VGet(-50, 0, -50), VGet(50, 0, 50));
}

void LightTest::Update()
{
	if (Input::anyKey)
		transform->position.x++;
	printfDx("light x : %f\n", transform->position.x);

	if (Input::IsKeyDown(KEY::KEY_ESCAPE))SceneManager::Get()->End();

	VECTOR3 v1(-50.f, 0.f, 50.f), v2(-50.f, 0.f, -50.f), v3(50.f, 0.f, 50.f), v4(50.f, 0.f, -50.f);

	DrawTriangle3D(v1, v2, v3, 0xffffffff, TRUE);
	DrawTriangle3D(v2, v3, v4, 0xffffffff, TRUE);

//	TestDrawShadowMap(shadow, 350, 250, 450, 350);

	//««‰e««//TODO

	//ShadowMap_DrawSetup(shadow);



	//ShadowMap_DrawEnd();
}
