#include "TestTransformChara.h"
#include "TestTransformComponent.h"

TestTransformChara::TestTransformChara()
{
}

TestTransformChara::~TestTransformChara()
{
}

void TestTransformChara::Start()
{
	AddComponent<TestTransformComponent>();
	ImageRenderer* imageRenderer = AddComponent<ImageRenderer>();
	imageRenderer->SetImage("..\\Media\\testCircle.png");
}
