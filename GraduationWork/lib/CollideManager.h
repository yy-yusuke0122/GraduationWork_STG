#pragma once

class CollideManager2D;
class CollideManager3D;
class Collider2D;
class Collider3D;

class CollideManager {
private:
	CollideManager();
	~CollideManager();
	static CollideManager* instance;
public:
	/// <summary>
	/// �C���X�^���X���擾����
	/// </summary>
	/// <returns>�C���X�^���X�̃|�C���^�[</returns>
	static CollideManager* Get();

	/// <summary>
	/// �C���X�^���X��j�󂷂�
	/// </summary>
	/// <returns>true:����, false:���ɔj�󂳂�Ă���</returns>
	static bool Destroy();

public:
	/// <summary>
	/// ������
	/// </summary>
	void Start();

	/// <summary>
	/// �����蔻����m�F
	/// </summary>
	void Update();

	/// <summary>
	/// �S�ẴR���C�_�[���Ǘ�������O��
	/// </summary>
	void RemoveAllCollider();

	/// <summary>
	/// Collider2D���Ǘ����ɒǉ�����
	/// </summary>
	/// <param name="_col">�ǉ�������Collider</param>
	/// <returns>true:����, false:���ɓo�^����Ă���</returns>
	bool PushCollider2D(Collider2D* _col);

	/// <summary>
	/// Collider3D���Ǘ����ɒǉ�����
	/// </summary>
	/// <param name="_col">�ǉ�������Collider</param>
	/// <returns>true:����, false:���ɓo�^����Ă���</returns>
	bool PushCollider3D(Collider3D* _col);

	/// <summary>
	/// �R���C�_�[���Ǘ�������O��
	/// �R���C�_�[�폜���Ɏ����ŌĂ΂��̂ŁA���ڌĂ΂Ȃ�����
	/// </summary>
	void RemoveCollider2D(Collider2D* _col);

	/// <summary>
	/// �R���C�_�[���Ǘ�������O��
	/// �R���C�_�[�폜���Ɏ����ŌĂ΂��̂ŁA���ڌĂ΂Ȃ�����
	/// </summary>
	void RemoveCollider3D(Collider3D* _col);

private:
	CollideManager2D* manager2D;
	CollideManager3D* manager3D;
};