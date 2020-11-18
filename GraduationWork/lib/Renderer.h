#pragma once

#include "Component.h"

class Renderer :public Component
{
public:
	Renderer();
	virtual ~Renderer();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() = 0;
	
	/// <summary>
	/// 非同期読み込み中か
	/// </summary>
	/// <returns>true：読み込み中、false：読み込み終了</returns>
	bool CheckAsync();

public:
	virtual void Initialize() = 0;

protected:
	void AddRendererToScene();

	virtual int CheckAsyncLoading() = 0;

private:
	//非同期読み込み中のエラー（初期化＆破棄）
	virtual void DestroyParam() = 0;

protected:
	mutable bool isAsync;

};
