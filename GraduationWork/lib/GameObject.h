#pragma once
#include <list>
#include <string>
#include <typeinfo>
#include "Object.h"

class Scene;
class Component;
class Transform;

class GameObject : public Object {
	friend Scene;
	friend class MapChip;
public:
	GameObject();
	virtual ~GameObject();

	void Update() final;
	virtual void PostUpdate();

	/// <summary>
	/// Componentを追加する
	/// </summary>
	/// <typeparam name="C">追加したいComponentのクラス</typeparam>
	/// <returns>追加したComponentのポインター</returns>
	template<class C>
	inline C* AddComponent();

	/// <summary>
	/// 指定したComponentを取得する
	/// </summary>
	/// <typeparam name="C">取得したいComponentのクラス</typeparam>
	/// <returns>成功で指定したComponentのポインター、失敗でnullptr</returns>
	template<class C>
	C* GetComponent();

	/// <summary>
	/// Componentリストを取得する
	/// </summary>
	/// <returns>成功:componentList</returns>
	std::list<Component*> GetComponentAll();

	/// <summary>
	/// 指定したComponentを破棄する
	/// </summary>
	/// <typeparam name="C">破棄したいComponentのクラス</typeparam>
	/// <returns>成功でtrue、指定したクラスのComponentが見つからなければfalse</returns>
	template<class C>
	bool RemoveComponent();

	/// <summary>
	/// 所持している全てのComponentを破棄する
	/// </summary>
	void RemoveComponentAll();

	/// <summary>
	/// 所持しているComponentから、破壊フラグが立っているものを破棄する
	/// </summary>
	void DestroyComponents();

	/// <summary>
	/// 存在しているシーンのポインターを返す
	/// </summary>
	/// <returns>存在しているシーンのポインター</returns>
	Scene* GetScene() const override;

	/// <summary>
	/// 親GameObjectを取得
	/// </summary>
	/// <returns>親GameObjectのポインター</returns>
	GameObject* GetParent() const;

	/// <summary>
	/// 親GameObjectをセットする
	/// </summary>
	/// <param name="_obj">親にしたいGameObjectのポインター</param>
	void SetParent(GameObject* _obj);

	/// <summary>
	/// 指定したタグの子GameObjectを抽出する
	/// </summary>
	/// <param name="_name">抽出したい子GameObjectのタグ</param>
	/// <returns>抽出したGameObjectのリスト</returns>
	std::list<GameObject*> GetChild(std::string _tag) const;

	/// <summary>
	/// 子GameObjectのリストを取得
	/// </summary>
	/// <returns>子GameObjectのリスト</returns>
	std::list<GameObject*> GetChildren() const;

	/// <summary>
	/// 子GameObjectを追加する
	/// </summary>
	/// <param name="_obj">追加したいGameObjectのポインター</param>
	/// <returns>成功でtrue、既に追加されている子GameObjectがあるとfalse</returns>
	bool SetChild(GameObject* _obj);

	/// <summary>
	/// 指定した子GameObjectを破棄する
	/// </summary>
	/// <param name="_name">破棄したい子GameObject</param>
	/// <returns>成功でtrue、指定したGameObjectが見つからなければfalse</returns>
	bool RemoveChild(GameObject* _obj);

	/// <summary>
	/// 指定したタグの子GameObjectを全て破棄する
	/// </summary>
	/// <param name="_tag">破棄したい子GameObjectのタグ</param>
	/// <returns>成功でtrue、指定したタグの子GameObjectが見つからなければfalse</returns>
	bool RemoveChild(std::string _tag);

	/// <summary>
	/// 子GameObjectを全て破棄する
	/// </summary>
	void RemoveChildren();

	/// <summary>
	/// GameObjectを生成する
	/// </summary>
	/// <typeparam name="C">生成したいクラス</typeparam>
	/// <param name="_tag">生成したGameObjectに付けるタグ</param>
	/// <returns>生成したGameObjectのポインター</returns>
	template<class C>
	inline C* Instantiate(std::string _tag = "");

	/// <summary>
	/// Objectの有効状態をセットする
	/// </summary>
	/// <param name="_active">有効にするならtrue</param>
	void SetActive(bool _active) final override;

private:
	std::list<Component*> compList;			// コンポーネントリスト
	GameObject* parent;						// 親オブジェクト
	std::list<GameObject*> children;		// 子オブジェクトのリスト
	Scene* scene;							// 存在しているシーンのポインター

	GameObject* func(GameObject*);

public:
	std::string tag;						// タグ
	Transform* transform;					// トランスフォーム
};

template<class C>
inline C* GameObject::AddComponent()
{
	// 既に同じComponentを持っていたら終了
	C* p = GetComponent<C>();
	if (p != nullptr) 
		return nullptr;

	// Componentを生成し、追加する
	p = new C();
	Component* comp = p;
	comp->gameObject = this;
	comp->transform = this->transform;
	Object* obj = comp;
	obj->className = typeid(C).name();
	compList.push_back(comp);
	comp->Start();

	return p;
}

template<class C>
inline C* GameObject::GetComponent()
{
	C* p = nullptr;

	// 対応するComponentを抽出
	for (auto comp : compList) {
		p = dynamic_cast<C*>(comp);
		if (p != nullptr)
			return p;
	}

	return nullptr;
}

template<class C>
inline bool GameObject::RemoveComponent()
{
	C* p = nullptr;

	// 対応するComponentの破壊フラグを立てる
	for (auto it = compList.begin(); it != compList.end(); ++it) {
		p = dynamic_cast<C*>(*it);
		if (p != nullptr) {
			Object* obj = p;
			obj->Destroy();
			return true;
		}
	}

	return false;
}

template<class C>
inline C* GameObject::Instantiate(std::string _name)
{
	C* p = reinterpret_cast<C*>(func(new C));
	Object* obj = p;
	obj->className = typeid(C).name();
	GameObject* gameObj = p;
	if (_name == "")
		gameObj->tag = obj->className.substr(6ull);
	else
		gameObj->tag = _name;
	gameObj->Start();

	return p;
}
