#include "Renderer.h"
#include "DrawManager.h"

Renderer::Renderer() :
	isAsync(false)
{
	DrawManager::Get()->AddRenderer(this);
}

Renderer::~Renderer()
{
	DrawManager::Get()->EraseRenderer(this);
	if (isAsync)
		GetScene()->EraseAsyncRenderer(this);
}

bool Renderer::CheckAsync() 
{
	int ret = CheckAsyncLoading();
	if (ret == 1)
		return true;

	if (ret == -1)//非同期読み込み中のエラー（設定したパラメータを初期化）
		DestroyParam();

	isAsync = false;
	return false;
}

void Renderer::AddRendererToScene()
{
	GetScene()->AddAsyncRenderer(this);
	isAsync = true;
}
