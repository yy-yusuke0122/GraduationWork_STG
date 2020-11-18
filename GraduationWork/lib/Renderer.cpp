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

	if (ret == -1)//�񓯊��ǂݍ��ݒ��̃G���[�i�ݒ肵���p�����[�^���������j
		DestroyParam();

	isAsync = false;
	return false;
}

void Renderer::AddRendererToScene()
{
	GetScene()->AddAsyncRenderer(this);
	isAsync = true;
}
