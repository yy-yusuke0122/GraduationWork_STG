#pragma once
#include <string>

class GameObject;

class Scene;

class Object {
	friend Scene;
	friend GameObject;
public:
	Object();
	virtual ~Object();

	virtual void Start();
	virtual void Update();

	/// <summary>
	/// ���O���擾
	/// </summary>
	/// <returns>���O�̕�����</returns>
	std::string GetTypeName() const;

	/// <summary>
	/// ���݂��Ă���V�[���̃|�C���^�[��Ԃ�
	/// </summary>
	/// <returns>���݂��Ă���V�[���̃|�C���^�[</returns>
	virtual Scene* GetScene() const = 0;

	/// <summary>
	/// Object�̗L���E�������擾
	/// </summary>
	/// <returns>Object�̗L�����</returns>
	bool IsActive() const;

	/// <summary>
	/// Object�̗L����Ԃ��Z�b�g����
	/// </summary>
	/// <param name="_active">�L���ɂ���Ȃ�true</param>
	virtual void SetActive(bool _active);

	/// <summary>
	/// Object�̔j��t���O���擾
	/// </summary>
	/// <returns>Object�̔j��t���O</returns>
	bool IsDestroy() const;

	/// <summary>
	/// Object�̔j��t���O�𗧂Ă�
	/// </summary>
	void Destroy();

	/// <summary>
	/// �V�[����FindGameObject���Ăт܂�
	/// </summary>
	/// <param name="_tag">�I�u�W�F�N�g�̃^�O</param>
	/// <returns>Scene��FindGameObject</returns>
	virtual GameObject* FindGameObject(const std::string& _tag);

private:
	std::string className;		// ���O
	bool active;				// �L�����
	bool isDestroy;				// �j��t���O
};
