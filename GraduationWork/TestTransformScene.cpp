#include "TestTransformScene.h"
#include "TestTransformChara.h"
#include "TestTransformComponent.h"

TestTransformScene::TestTransformScene()
{
	obj = Instantiate<TestTransformChara>();
	obj2 = Instantiate<TestTransformChara>();
	obj3 = Instantiate<TestTransformChara>();
	obj->SetChild(obj2);
	obj2->SetChild(obj3);
}

TestTransformScene::~TestTransformScene()
{
}

void TestTransformScene::Start()
{
	obj->GetComponent<TestTransformComponent>()->UseControl(true);
	VECTOR3 center = { (float)(Screen::x / 2), (float)(Screen::y / 2), 0.0f };
	obj->transform->SetPosition(center);
	VECTOR3 dif = { 200.0f, 0.0f, 0.0f };
	obj2->transform->AddPosition(dif);
	obj3->transform->AddPosition(dif);
}

void TestTransformScene::Update()
{
}
