#pragma once
#include "SceneManager.h"

class Transform;
class Collider3D;
class Collider2D;

class Component : public Object {
public:
	Component();
	virtual ~Component();

	virtual void Start();
	virtual void Update();

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
	/// GameObjectを生成する
	/// </summary>
	/// <typeparam name="C">生成したいGameObjectのクラス</typeparam>
	/// <returns>生成したGameObjectのポインター</returns>
	template<class C>
	inline C* Instantiate();

	/// <summary>
	/// 存在しているシーンのポインターを返す
	/// </summary>
	/// <returns>存在しているシーンのポインター</returns>
	Scene* GetScene() const override;

	virtual void OnCollisionEnter2D(Collider2D* _collider) {}
	virtual void OnCollisionStay2D(Collider2D* _collider) {}
	virtual void OnCollisionExit2D(Collider2D* _collider) {}
	virtual void OnTriggerEnter2D(Collider2D* _collider) {}
	virtual void OnTriggerStay2D(Collider2D* _collider) {}
	virtual void OnTriggerExit2D(Collider2D* _collider) {}
	virtual void OnCollisionEnter(Collider3D* _collider) {}
	virtual void OnCollisionStay(Collider3D* _collider) {}
	virtual void OnCollisionExit(Collider3D* _collider) {}
	virtual void OnTriggerEnter(Collider3D* _collider) {}
	virtual void OnTriggerStay(Collider3D* _collider) {}
	virtual void OnTriggerExit(Collider3D* _collider) {}

public:
	Transform* transform;			// 所有者のトランスフォーム
	GameObject* gameObject;			// 所有者のポインター

private:

};

template<class C>
inline C* Component::AddComponent()
{
	return gameObject->AddComponent<C>();
}

template<class C>
inline C* Component::GetComponent()
{
	return gameObject->GetComponent<C>();
}

template<class C>
inline bool Component::RemoveComponent()
{
	return gameObject->RemoveComponent<C>();
}

template<class C>
inline C* Component::Instantiate()
{
	return SceneManager::GetCurrentScene()->Instantiate<C>();
}
