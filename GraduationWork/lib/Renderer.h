#pragma once

#include "Component.h"

class Renderer :public Component
{
public:
	Renderer();
	virtual ~Renderer();

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;
	
	/// <summary>
	/// �񓯊��ǂݍ��ݒ���
	/// </summary>
	/// <returns>true�F�ǂݍ��ݒ��Afalse�F�ǂݍ��ݏI��</returns>
	bool CheckAsync();

public:
	virtual void Initialize() = 0;

protected:
	void AddRendererToScene();

	virtual int CheckAsyncLoading() = 0;

private:
	//�񓯊��ǂݍ��ݒ��̃G���[�i���������j���j
	virtual void DestroyParam() = 0;

protected:
	mutable bool isAsync;

};
