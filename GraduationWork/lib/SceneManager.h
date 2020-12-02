#pragma once

#include "Scene.h"

class Renderer;

class SceneManager
{
private:
	/// <summary>
	/// シーン生成
	/// </summary>
	/// <typeparam name="C">シーン型</typeparam>
	/// <param name="_name">シーン名</param>
	/// <returns>生成したシーンのアドレス</returns>
	template<class C>
	static Scene* CreateScene() { return new C; }

private:
	SceneManager()
	{
	}

	~SceneManager() 
	{
	}

public:
	/// <summary>
	/// インスタンス破棄
	/// </summary>
	/// <returns>true：破棄、false：生成されていない</returns>
	static bool Destroy();

	/// <summary>
	/// 初期化
	/// </summary>
	static void Start();

	/// <summary>
	/// 更新
	/// </summary>
	static void Update();

	/// <summary>
	/// シーン切り替え
	/// </summary>
	/// <typeparam name="C">切り替えるシーン</typeparam>
	template<class C>
	static void LoadScene()
	{
		sceneName = typeid(C).name();
		createScene = CreateScene<C>;
	}

	/// <summary>
	/// メインシーンにサブシーンを追加
	/// </summary>
	/// <typeparam name="C">追加するサブシーン</typeparam>
	/// <returns>true：成功、false：メインシーンが生成されていない</returns>
	template<class C>
	static bool AddSubScene()
	{
		if (mainScene == nullptr)return false;

		return mainScene->AddSubScene<C>();
	}

	/// <summary>
	/// メインシーンからサブシーンを破棄
	/// </summary>
	/// <typeparam name="C">破棄するサブシーン</typeparam>
	/// <returns>true：サブシーンの破棄、false：メインシーンが生成されていない</returns>
	template<class C>
	static bool DestroySubScene()
	{
		if (mainScene == nullptr)return false;

		return mainScene->DestroySubScene<C>();
	}

	/// <summary>
	/// メインシーン取得
	/// </summary>
	/// <typeparam name="C">メインシーンの型</typeparam>
	/// <returns>メインシーン取得</returns>
	template<class C>
	static C* GetMainScene() { return dynamic_cast<C*>(mainScene); }

	/// <summary>
	/// 現在のシーンを取得
	/// </summary>
	/// <returns>現在のシーン</returns>
	static Scene* GetCurrentScene() { return Scene::GetCurrentScene(); }

	/// <summary>
	/// 非同期読み込み中のファイル数を取得
	/// </summary>
	/// <returns>非同期読み込み中のファイル数</returns>
	static int GetAsyncLoadAllCount();

	/// <summary>
	/// 終了フラグを立てる
	/// </summary>
	static void End() { isEnd = true; }

	/// <summary>
	/// 終了フラグ取得
	/// </summary>
	/// <returns>true：終了、false：続行</returns>
	static bool IsEnd() { return isEnd; }

private:
	/// <summary>
	/// シーン切り替え
	/// </summary>
	static void ChangeScene();

private:
	static Scene* mainScene;//メインシーン

	static Scene* (*createScene)();//メインシーン切り替え関数

	static std::string sceneName;//メインシーン名

private:
	static bool isEnd;//終了フラグ

public:
	static bool isAsyncLoad;//Loader・Sceneで画像・音・モデル・ファイルを非同期で読み込むか

};
