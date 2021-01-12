#pragma once

#include <list>
#include <unordered_map>
#include <string>

class Renderer;

class Light;

class DrawManager
{
private:
	DrawManager() {}
	~DrawManager() {}

public:
	/// <summary>
	/// インスタンス破棄
	/// </summary>
	static void Destroy();

	/// <summary>
	/// 登録された描画オブジェクトの描画
	/// </summary>
	static void Draw();

	/// <summary>
	/// 描画オブジェクト追加
	/// </summary>
	/// <param name="_p">追加する描画オブジェクト</param>
	static std::list<Renderer*>::iterator AddRenderer(Renderer* _p);

	/// <summary>
	/// 描画オブジェクト追加
	/// </summary>
	/// <param name="_p">追加する描画オブジェクト</param>
	static std::list<Renderer*>::iterator AddRenderer(std::list<Renderer*>::iterator _p);

	/// <summary>
	/// 描画オブジェクト破棄
	/// </summary>
	/// <param name="_p">破棄する描画オブジェクト</param>
	/// <returns>true：破棄、false：存在しない</returns>
	static bool EraseRenderer(Renderer* _p);

	/// <summary>
	/// ライトオブジェクト追加
	/// </summary>
	static void AddLight(Light* _p);

	/// <summary>
	/// ライトオブジェクト破棄
	/// </summary>
	/// <returns>true：破棄、false：存在しない</returns>
	static bool EraseLight(Light* _p);

private:
	static std::list<Renderer*> rendererList;	//描画リスト
	static std::list<Light*> lightList;		//ライトリスト

//	int shadowHandle;//シャドウマップのハンドル：TODO 3つまで設定可能なので増やしましょう

};
