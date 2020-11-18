#include "AnimTestScene.h"
#include "Player.h"
#include "AnimTestComp.h"

AnimTestScene::AnimTestScene()
{
	player = Instantiate<Player>();
}

AnimTestScene::~AnimTestScene()
{
}

void AnimTestScene::Start()
{
	player->GetComponent<ImageRenderer>()->SetImageDiv("../Media/testImage.png", 2, 2, 4);
	animTestComp = player->AddComponent<AnimTestComp>();
	animTestComp->SetStartAnim("Idle");
	player->transform->SetPosition(VGet(300.0f, 100.0f, 0.0f));
}

void AnimTestScene::Update()
{
	if (Input::IsKeyDown(KEY::KEY_0)) animTestComp->SetBool("isWalk", true);
	if (Input::IsKeyDown(KEY::KEY_1)) animTestComp->SetBool("isWalk", false);
	if (Input::IsKeyPush(KEY::KEY_RIGHT)) {
		animTestComp->GetCurrentAnim()->speed += 1.0f;
	}
	else if (Input::IsKeyPush(KEY::KEY_LEFT)) {
		animTestComp->GetCurrentAnim()->speed -= 1.0f;
	}
}
