#pragma once

#include "AsyncComponent.h"

class Renderer :public AsyncComponent
{
public:
	Renderer();
	virtual ~Renderer();

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;

public:
	/// <summary>
	/// �`�揇��ݒ�
	/// </summary>
	/// <param name="_order">�`�揇</param>
	void SetOrder(int _order);

	/// <summary>
	/// �`�揇���擾
	/// </summary>
	/// <returns>�`�揇</returns>
	int GetOrder()const { return order; }

private:
	void AsyncEnd()override { isRendererEnable = true; }

public:
	bool isRendererEnable;//�`�� �I���E�I�t

private:
	std::list<Renderer*>::iterator orderIt;

	int order;//�`��̏��ԁi0����j

};
