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

public:
	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static SceneManager* Get();

private:
	SceneManager():
		mainScene(nullptr), createScene(nullptr), isEnd(false), isAsyncLoad(false)
	{
	}

	~SceneManager();

public:
	/// <summary>
	/// インスタンス破棄
	/// </summary>
	/// <returns>true：破棄、false：生成されていない</returns>
	bool Destroy();

	/// <summary>
	/// 初期化
	/// </summary>
	void Start();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// シーン切り替え
	/// </summary>
	/// <typeparam name="C">切り替えるシーン</typeparam>
	template<class C>
	void LoadScene()
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
	bool AddSubScene()
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
	bool DestroySubScene()const
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
	C* GetMainScene()const { return dynamic_cast<C*>(mainScene); }

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
	void End() { isEnd = true; }

	/// <summary>
	/// 終了フラグ取得
	/// </summary>
	/// <returns>true：終了、false：続行</returns>
	bool IsEnd()const { return isEnd; }

private:
	/// <summary>
	/// シーン切り替え
	/// </summary>
	void ChangeScene();

private:
	Scene* mainScene;//メインシーン

	Scene* (*createScene)();//メインシーン切り替え関数

	std::string sceneName;//メインシーン名

	static SceneManager* instance;//SceneManagerのインスタンス

private:
	bool isEnd;//終了フラグ

public:
	bool isAsyncLoad;//Loader・Sceneで画像・音・モデル・ファイルを非同期で読み込むか

};
