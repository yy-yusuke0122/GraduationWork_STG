#pragma once

#include "Scene.h"

class Renderer;

class SceneManager
{
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
	SceneManager()
	{
	}

	~SceneManager() 
	{
	}

public:
	/// <summary>
	/// �C���X�^���X�j��
	/// </summary>
	/// <returns>true�F�j���Afalse�F��������Ă��Ȃ�</returns>
	static bool Destroy();

	/// <summary>
	/// ������
	/// </summary>
	static void Start();

	/// <summary>
	/// �X�V
	/// </summary>
	static void Update();

	/// <summary>
	/// �V�[���؂�ւ�
	/// </summary>
	/// <typeparam name="C">�؂�ւ���V�[��</typeparam>
	template<class C>
	static void LoadScene()
	{
		sceneName = typeid(C).name();
		createScene = CreateScene<C>;
	}

	/// <summary>
	/// ���C���V�[���ɃT�u�V�[����ǉ�
	/// </summary>
	/// <typeparam name="C">�ǉ�����T�u�V�[��</typeparam>
	/// <returns>true�F�����Afalse�F���C���V�[������������Ă��Ȃ�</returns>
	template<class C>
	static bool AddSubScene()
	{
		if (mainScene == nullptr)return false;

		return mainScene->AddSubScene<C>();
	}

	/// <summary>
	/// ���C���V�[������T�u�V�[����j��
	/// </summary>
	/// <typeparam name="C">�j������T�u�V�[��</typeparam>
	/// <returns>true�F�T�u�V�[���̔j���Afalse�F���C���V�[������������Ă��Ȃ�</returns>
	template<class C>
	static bool DestroySubScene()
	{
		if (mainScene == nullptr)return false;

		return mainScene->DestroySubScene<C>();
	}

	/// <summary>
	/// ���C���V�[���擾
	/// </summary>
	/// <typeparam name="C">���C���V�[���̌^</typeparam>
	/// <returns>���C���V�[���擾</returns>
	template<class C>
	static C* GetMainScene() { return dynamic_cast<C*>(mainScene); }

	/// <summary>
	/// ���݂̃V�[�����擾
	/// </summary>
	/// <returns>���݂̃V�[��</returns>
	static Scene* GetCurrentScene() { return Scene::GetCurrentScene(); }

	/// <summary>
	/// �񓯊��ǂݍ��ݒ��̃t�@�C�������擾
	/// </summary>
	/// <returns>�񓯊��ǂݍ��ݒ��̃t�@�C����</returns>
	static int GetAsyncLoadAllCount();

	/// <summary>
	/// �I���t���O�𗧂Ă�
	/// </summary>
	static void End() { isEnd = true; }

	/// <summary>
	/// �I���t���O�擾
	/// </summary>
	/// <returns>true�F�I���Afalse�F���s</returns>
	static bool IsEnd() { return isEnd; }

private:
	/// <summary>
	/// �V�[���؂�ւ�
	/// </summary>
	static void ChangeScene();

private:
	static Scene* mainScene;//���C���V�[��

	static Scene* (*createScene)();//���C���V�[���؂�ւ��֐�

	static std::string sceneName;//���C���V�[����

private:
	static bool isEnd;//�I���t���O

public:
	static bool isAsyncLoad;//Loader�EScene�ŉ摜�E���E���f���E�t�@�C����񓯊��œǂݍ��ނ�

};
