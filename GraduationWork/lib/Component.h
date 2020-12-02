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
	/// Component��ǉ�����
	/// </summary>
	/// <typeparam name="C">�ǉ�������Component�̃N���X</typeparam>
	/// <returns>�ǉ�����Component�̃|�C���^�[</returns>
	template<class C>
	inline C* AddComponent();

	/// <summary>
	/// �w�肵��Component���擾����
	/// </summary>
	/// <typeparam name="C">�擾������Component�̃N���X</typeparam>
	/// <returns>�����Ŏw�肵��Component�̃|�C���^�[�A���s��nullptr</returns>
	template<class C>
	C* GetComponent();

	/// <summary>
	/// Component���X�g���擾����
	/// </summary>
	/// <returns>����:componentList</returns>
	std::list<Component*> GetComponentAll();

	/// <summary>
	/// �w�肵��Component��j������
	/// </summary>
	/// <typeparam name="C">�j��������Component�̃N���X</typeparam>
	/// <returns>������true�A�w�肵���N���X��Component��������Ȃ����false</returns>
	template<class C>
	bool RemoveComponent();

	/// <summary>
	/// GameObject�𐶐�����
	/// </summary>
	/// <typeparam name="C">����������GameObject�̃N���X</typeparam>
	/// <returns>��������GameObject�̃|�C���^�[</returns>
	template<class C>
	inline C* Instantiate();

	/// <summary>
	/// ���݂��Ă���V�[���̃|�C���^�[��Ԃ�
	/// </summary>
	/// <returns>���݂��Ă���V�[���̃|�C���^�[</returns>
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
	Transform* transform;			// ���L�҂̃g�����X�t�H�[��
	GameObject* gameObject;			// ���L�҂̃|�C���^�[

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
