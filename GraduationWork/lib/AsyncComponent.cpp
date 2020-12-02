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

	if (ret == -1)//非同期読み込み中のエラー（設定したパラメータを初期化）
		DestroyParam();

	isAsync = false;
	
	return false;
}

void AsyncComponent::AddRendererToScene()
{
	GetScene()->AddAsync(this);
	isAsync = true;
}
