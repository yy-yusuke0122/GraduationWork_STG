#pragma once

#include "Component.h"

class AsyncComponent :public Component
{
public:
	AsyncComponent() :
		isAsync(false)
	{
	}

	virtual ~AsyncComponent();

	/// <summary>
	/// �񓯊��ǂݍ��ݒ���
	/// </summary>
	/// <returns>true�F�ǂݍ��ݒ��Afalse�F�ǂݍ��ݏI��</returns>
	bool CheckAsync();

public:
	virtual void Initialize() {}

protected:
	void AddRendererToScene();

	virtual int CheckAsyncLoading() = 0;

private:
	//�񓯊��ǂݍ��ݒ��̃G���[�i���������j���j
	virtual void DestroyParam() = 0;

protected:
	mutable bool isAsync;

};
