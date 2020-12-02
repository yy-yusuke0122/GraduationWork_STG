#include "AsyncComponent.h"

AsyncComponent::~AsyncComponent()
{
	if (isAsync)
		GetScene()->EraseAsync(this);
}

bool AsyncComponent::CheckAsync()
{
	int ret = CheckAsyncLoading();
	if (ret == 1)
		return true;

	if (ret == -1)//�񓯊��ǂݍ��ݒ��̃G���[�i�ݒ肵���p�����[�^���������j
		DestroyParam();

	isAsync = false;
	
	return false;
}

void AsyncComponent::AddRendererToScene()
{
	GetScene()->AddAsync(this);
	isAsync = true;
}
