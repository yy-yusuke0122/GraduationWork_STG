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
	/// �������Ă���S�Ă�Component��j������
	/// </summary>
	void RemoveComponentAll();

	/// <summary>
	/// �������Ă���Component����A�j��t���O�������Ă�����̂�j������
	/// </summary>
	void DestroyComponents();

	/// <summary>
	/// ���݂��Ă���V�[���̃|�C���^�[��Ԃ�
	/// </summary>
	/// <returns>���݂��Ă���V�[���̃|�C���^�[</returns>
	Scene* GetScene() const override;

	/// <summary>
	/// �eGameObject���擾
	/// </summary>
	/// <returns>�eGameObject�̃|�C���^�[</returns>
	GameObject* GetParent() const;

	/// <summary>
	/// �eGameObject���Z�b�g����
	/// </summary>
	/// <param name="_obj">�e�ɂ�����GameObject�̃|�C���^�[</param>
	void SetParent(GameObject* _obj);

	/// <summary>
	/// �w�肵���^�O�̎qGameObject�𒊏o����
	/// </summary>
	/// <param name="_name">���o�������qGameObject�̃^�O</param>
	/// <returns>���o����GameObject�̃��X�g</returns>
	std::list<GameObject*> GetChild(std::string _tag) const;

	/// <summary>
	/// �qGameObject�̃��X�g���擾
	/// </summary>
	/// <returns>�qGameObject�̃��X�g</returns>
	std::list<GameObject*> GetChildren() const;

	/// <summary>
	/// �qGameObject��ǉ�����
	/// </summary>
	/// <param name="_obj">�ǉ�������GameObject�̃|�C���^�[</param>
	/// <returns>������true�A���ɒǉ�����Ă���qGameObject�������false</returns>
	bool SetChild(GameObject* _obj);

	/// <summary>
	/// �w�肵���qGameObject��j������
	/// </summary>
	/// <param name="_name">�j���������qGameObject</param>
	/// <returns>������true�A�w�肵��GameObject��������Ȃ����false</returns>
	bool RemoveChild(GameObject* _obj);

	/// <summary>
	/// �w�肵���^�O�̎qGameObject��S�Ĕj������
	/// </summary>
	/// <param name="_tag">�j���������qGameObject�̃^�O</param>
	/// <returns>������true�A�w�肵���^�O�̎qGameObject��������Ȃ����false</returns>
	bool RemoveChild(std::string _tag);

	/// <summary>
	/// �qGameObject��S�Ĕj������
	/// </summary>
	void RemoveChildren();

	/// <summary>
	/// GameObject�𐶐�����
	/// </summary>
	/// <typeparam name="C">�����������N���X</typeparam>
	/// <param name="_tag">��������GameObject�ɕt����^�O</param>
	/// <returns>��������GameObject�̃|�C���^�[</returns>
	template<class C>
	inline C* Instantiate(std::string _tag = "");

	/// <summary>
	/// Object�̗L����Ԃ��Z�b�g����
	/// </summary>
	/// <param name="_active">�L���ɂ���Ȃ�true</param>
	void SetActive(bool _active) final override;

private:
	std::list<Component*> compList;			// �R���|�[�l���g���X�g
	GameObject* parent;						// �e�I�u�W�F�N�g
	std::list<GameObject*> children;		// �q�I�u�W�F�N�g�̃��X�g
	Scene* scene;							// ���݂��Ă���V�[���̃|�C���^�[

	GameObject* func(GameObject*);

public:
	std::string tag;						// �^�O
	Transform* transform;					// �g�����X�t�H�[��
};

template<class C>
inline C* GameObject::AddComponent()
{
	// ���ɓ���Component�������Ă�����I��
	C* p = GetComponent<C>();
	if (p != nullptr) 
		return nullptr;

	// Component�𐶐����A�ǉ�����
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

	// �Ή�����Component�𒊏o
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

	// �Ή�����Component�̔j��t���O�𗧂Ă�
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
