#pragma once

#include <list>
#include <vector>
#include <string>
#include <typeinfo>
#include <new>
#include "GameObject.h"
#include "SceneOption.h"

class SceneManager;
class AsyncComponent;
class Sound;

class Scene :public Object
{
	friend SceneManager;

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
	struct NODE
	{
		Scene* (*createScene)();//生成するシーンの関数
		std::string name;//生成するシーン名
	};

public:
	Scene() :
		isReload(false), reloadScene(nullptr), isAsyncLoad(false), parentScene(nullptr),
		asyncScene(nullptr), asyncMinTime(0.5f), asyncTime(0.5f), asyncUseTime(0.5f)
	{
		asyncNode.createScene = nullptr;
	}

	virtual~Scene();

	/// <summary>
	/// 初期化
	/// </summary>
	void SceneStart();

	/// <summary>
	/// 更新
	/// </summary>
	void SceneUpdate();

	/// <summary>
	/// サブシーン追加
	/// </summary>
	/// <typeparam name="C">追加するサブシーン</typeparam>
	/// <returns>true：成功、false：既に存在している</returns>
	template<class C>
	bool AddSubScene()
	{
		std::string name = typeid(C).name();

		for (std::list<NODE>::iterator it = addSceneList.begin(), end = addSceneList.end(); it != end; ++it)
			if (name == it->name)return false;
		for (std::list<Scene*>::iterator it = subSceneList.begin(), end = subSceneList.end(); it != end; ++it)
			if (name == (*it)->GetTypeName())return false;

		NODE node;
		node.name = name;
		node.createScene = CreateScene<C>;

		addSceneList.emplace_back(node);

		return true;
	}

	/// <summary>
	/// サブシーン破棄
	/// </summary>
	/// <typeparam name="C">破棄するサブシーン</typeparam>
	/// <returns>true：成功、false：存在しない</returns>
	template<class C>
	bool DestroySubScene()
	{
		std::string name = typeid(C).name();

		for (std::list<Scene*>::iterator it = subSceneList.begin(), end = subSceneList.end(); it != end; ++it)
		{
			if (name == (*it)->GetTypeName())
			{
				(*it)->Destroy();
				return true;
			}
		}
		for (std::list<NODE>::iterator it = addSceneList.begin(), end = addSceneList.end(); it != end; ++it)
		{
			if (name == it->name)
			{
				addSceneList.erase(it);
				return true;
			}
		}
		return false;
	}

	/// <summary>
	/// サブシーン取得
	/// </summary>
	/// <typeparam name="C">取得するサブシーン</typeparam>
	/// <returns>null以外：サブシーンのアドレス、null：存在しない</returns>
	template<class C>
	C* GetSubScene()
	{
		C* p = nullptr;
		for (std::list<Scene*>::iterator it = subSceneList.begin(), end = subSceneList.end(); it != end; ++it)
		{
			p = dynamic_cast<C*>(*it);
			if (p != nullptr)
				return p;
		}
		return nullptr;
	}

	/// <summary>
	/// サブシーン数取得
	/// </summary>
	/// <returns>サブシーン数</returns>
	int GetSubSceneCount()const;

	/// <summary>
	/// ゲームオブジェクトを探しますよ！！！
	/// </summary>
	/// <param name="_tag">タグ</param>
	/// <returns>アドレス！！！</returns>
	GameObject* FindGameObject(const std::string& _tag)override;

	/// <summary>
	/// ゲームオブジェクトを探しますよ！！！
	/// </summary>
	/// <returns>アドレス！！！</returns>
	template<class C>
	C* FindGameObject()
	{
		for (std::list<GameObject*>::iterator it = objectList.begin(), end = objectList.end(); it != end; ++it)
		{
			C* p = dynamic_cast<C*>(*it);
			if (p != nullptr)
				return p;
		}
		return nullptr;
	}

	/// <summary>
	/// ゲームオブジェクト生成
	/// </summary>
	/// <typeparam name="C">生成するオブジェクト</typeparam>
	/// <param name="_tagName">生成するオブジェクト名</param>
	/// <returns>生成したオブジェクト</returns>
	template<class C>
	C* Instantiate(std::string _tagName = "")
	{
		GameObject* obj = new C;
		obj->scene = this;

		Object* p = obj;
		p->className = typeid(C).name();

		if (_tagName == "") {
			obj->tag = p->className.substr(6ull);
		}
		else
			obj->tag = _tagName;

		objectList.emplace_back(obj);

		obj->Start();

		return reinterpret_cast<C*>(obj);
	}
	
	/// <summary>
	/// 再読み込み
	/// </summary>
	void Reload() { isReload = true; }

	/// <summary>
	/// 現在のシーンを取得
	/// </summary>
	/// <returns>現在のシーン</returns>
	static Scene* GetCurrentScene() { return currentScene; }

	/// <summary>
	/// シーンを取得
	/// </summary>
	/// <returns>シーンアドレス</returns>
	Scene* GetScene()const override { return const_cast<Scene*>(this); }

	/// <summary>
	/// 親シーン取得
	/// </summary>
	/// <returns>null以外：親アドレス、null：親無し</returns>
	Scene* GetParentScene()const { return parentScene; }

	/// <summary>
	/// 非同期読み込み中のファイル数を取得
	/// </summary>
	/// <returns>非同期読み込み中ファイル数</returns>
	int GetAsyncLoadCount()const;

	/// <summary>
	/// 非同期読み込み中のファイル数を取得（サブシーン含む）
	/// </summary>
	/// <returns>非同期読み込み中ファイル数</returns>
	int GetAsyncLoadCountWithSubScene()const;

public:
	/// <summary>
	/// 非同期読み込み中に生成されるシーンを設定
	/// 非同期読み込み終了時、自動で破棄されます
	/// </summary>
	/// <typeparam name="C"></typeparam>
	template<class C>
	void AsyncScene()
	{
		std::string name = typeid(C).name();

		asyncNode.name = name;
		asyncNode.createScene = CreateScene<C>;

		asyncUseTime = asyncMinTime;
	}

public:
	bool AddGameObject(GameObject* _object);

	void AddAsync(AsyncComponent* _async);

	void EraseAsync(AsyncComponent* _async);

private://SceneManagerで使用
	void SetName(const std::string& _name) { className = _name; }

	/// <summary>
	/// 再読み込みフラグを取得
	/// </summary>
	/// <returns>true：フラグが立っている、false：フラグが立ってない</returns>
	bool IsReload()const { return isReload; }

private:
	/// <summary>
	/// 死亡フラグが立っているオブジェクトを破棄
	/// </summary>
	void DestroyGameObjects();

private:
	std::list<GameObject*> objectList;//オブジェクトリスト

	std::list<Scene*> subSceneList;//サブシーンリスト

	std::list<NODE> addSceneList;//次フレームで追加するサブシーンリスト

	static Scene* currentScene;//現在のシーン

	bool isReload;//リロードフラグ

	Scene* (*reloadScene)();//シーンの再読み込み

	Scene* parentScene;//親シーン

	std::list<AsyncComponent*> asyncList;//非同期読み込みコンポーネント

	std::list<AsyncComponent*> asyncWaitList;//全体が読み終わるまで保存

private://非同期用変数
	NODE asyncNode;

	Scene* asyncScene;

	float asyncTime;

	float asyncUseTime;//一時保存

public:
	bool isAsyncLoad;//子シーン生成時に画像・音・モデルを非同期で読み込むか

	float asyncMinTime;//非同期シーン最低生存時間

	SceneOption option;
};
