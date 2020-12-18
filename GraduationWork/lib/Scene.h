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
	/// �V�[������
	/// </summary>
	/// <typeparam name="C">�V�[���^</typeparam>
	/// <param name="_name">�V�[����</param>
	/// <returns>���������V�[���̃A�h���X</returns>
	template<class C>
	static Scene* CreateScene() { return new C; }

private:
	struct NODE
	{
		Scene* (*createScene)();//��������V�[���̊֐�
		std::string name;//��������V�[����
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
	/// ������
	/// </summary>
	void SceneStart();

	/// <summary>
	/// �X�V
	/// </summary>
	void SceneUpdate();

	/// <summary>
	/// �T�u�V�[���ǉ�
	/// </summary>
	/// <typeparam name="C">�ǉ�����T�u�V�[��</typeparam>
	/// <returns>true�F�����Afalse�F���ɑ��݂��Ă���</returns>
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
	/// �T�u�V�[���j��
	/// </summary>
	/// <typeparam name="C">�j������T�u�V�[��</typeparam>
	/// <returns>true�F�����Afalse�F���݂��Ȃ�</returns>
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
	/// �T�u�V�[���擾
	/// </summary>
	/// <typeparam name="C">�擾����T�u�V�[��</typeparam>
	/// <returns>null�ȊO�F�T�u�V�[���̃A�h���X�Anull�F���݂��Ȃ�</returns>
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
	/// �T�u�V�[�����擾
	/// </summary>
	/// <returns>�T�u�V�[����</returns>
	int GetSubSceneCount()const;

	/// <summary>
	/// �Q�[���I�u�W�F�N�g��T���܂���I�I�I
	/// </summary>
	/// <param name="_tag">�^�O</param>
	/// <returns>�A�h���X�I�I�I</returns>
	GameObject* FindGameObject(const std::string& _tag)override;

	/// <summary>
	/// �Q�[���I�u�W�F�N�g��T���܂���I�I�I
	/// </summary>
	/// <returns>�A�h���X�I�I�I</returns>
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
	/// �Q�[���I�u�W�F�N�g����
	/// </summary>
	/// <typeparam name="C">��������I�u�W�F�N�g</typeparam>
	/// <param name="_tagName">��������I�u�W�F�N�g��</param>
	/// <returns>���������I�u�W�F�N�g</returns>
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
	/// �ēǂݍ���
	/// </summary>
	void Reload() { isReload = true; }

	/// <summary>
	/// ���݂̃V�[�����擾
	/// </summary>
	/// <returns>���݂̃V�[��</returns>
	static Scene* GetCurrentScene() { return currentScene; }

	/// <summary>
	/// �V�[�����擾
	/// </summary>
	/// <returns>�V�[���A�h���X</returns>
	Scene* GetScene()const override { return const_cast<Scene*>(this); }

	/// <summary>
	/// �e�V�[���擾
	/// </summary>
	/// <returns>null�ȊO�F�e�A�h���X�Anull�F�e����</returns>
	Scene* GetParentScene()const { return parentScene; }

	/// <summary>
	/// �񓯊��ǂݍ��ݒ��̃t�@�C�������擾
	/// </summary>
	/// <returns>�񓯊��ǂݍ��ݒ��t�@�C����</returns>
	int GetAsyncLoadCount()const;

	/// <summary>
	/// �񓯊��ǂݍ��ݒ��̃t�@�C�������擾�i�T�u�V�[���܂ށj
	/// </summary>
	/// <returns>�񓯊��ǂݍ��ݒ��t�@�C����</returns>
	int GetAsyncLoadCountWithSubScene()const;

public:
	/// <summary>
	/// �񓯊��ǂݍ��ݒ��ɐ��������V�[����ݒ�
	/// �񓯊��ǂݍ��ݏI�����A�����Ŕj������܂�
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

private://SceneManager�Ŏg�p
	void SetName(const std::string& _name) { className = _name; }

	/// <summary>
	/// �ēǂݍ��݃t���O���擾
	/// </summary>
	/// <returns>true�F�t���O�������Ă���Afalse�F�t���O�������ĂȂ�</returns>
	bool IsReload()const { return isReload; }

private:
	/// <summary>
	/// ���S�t���O�������Ă���I�u�W�F�N�g��j��
	/// </summary>
	void DestroyGameObjects();

private:
	std::list<GameObject*> objectList;//�I�u�W�F�N�g���X�g

	std::list<Scene*> subSceneList;//�T�u�V�[�����X�g

	std::list<NODE> addSceneList;//���t���[���Œǉ�����T�u�V�[�����X�g

	static Scene* currentScene;//���݂̃V�[��

	bool isReload;//�����[�h�t���O

	Scene* (*reloadScene)();//�V�[���̍ēǂݍ���

	Scene* parentScene;//�e�V�[��

	std::list<AsyncComponent*> asyncList;//�񓯊��ǂݍ��݃R���|�[�l���g

	std::list<AsyncComponent*> asyncWaitList;//�S�̂��ǂݏI���܂ŕۑ�

private://�񓯊��p�ϐ�
	NODE asyncNode;

	Scene* asyncScene;

	float asyncTime;

	float asyncUseTime;//�ꎞ�ۑ�

public:
	bool isAsyncLoad;//�q�V�[���������ɉ摜�E���E���f����񓯊��œǂݍ��ނ�

	float asyncMinTime;//�񓯊��V�[���Œᐶ������

	SceneOption option;
};
