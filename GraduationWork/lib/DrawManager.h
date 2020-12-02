#pragma once

#include <list>
#include <unordered_map>
#include <string>

class Renderer;

class Light;

class DrawManager
{
public:
	DrawManager() {}
	~DrawManager();

	/// <summary>
	/// �C���X�^���X�擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static DrawManager* Get();

	/// <summary>
	/// �C���X�^���X�j��
	/// </summary>
	/// <returns>true�F�j���Afalse�F��������Ă��Ȃ�</returns>
	bool Destroy();

	/// <summary>
	/// �o�^���ꂽ�`��I�u�W�F�N�g�̕`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �`��I�u�W�F�N�g�ǉ�
	/// </summary>
	/// <param name="_p">�ǉ�����`��I�u�W�F�N�g</param>
	void AddRenderer(Renderer* _p);

	/// <summary>
	/// �`��I�u�W�F�N�g�j��
	/// </summary>
	/// <param name="_p">�j������`��I�u�W�F�N�g</param>
	/// <returns>true�F�j���Afalse�F���݂��Ȃ�</returns>
	bool EraseRenderer(Renderer* _p);

	/// <summary>
	/// ���C�g�I�u�W�F�N�g�ǉ�
	/// </summary>
	void AddRight(Light* _p);

	/// <summary>
	/// ���C�g�I�u�W�F�N�g�j��
	/// </summary>
	/// <returns>true�F�j���Afalse�F���݂��Ȃ�</returns>
	bool EraseLight(Light* _p);

private:
	std::list<Renderer*> rendererList;	//�`�惊�X�g
	std::list<Light*> lightList;		//���C�g���X�g
	static DrawManager* instance;

	int shadowHandle;//�V���h�E�}�b�v�̃n���h���FTODO 3�܂Őݒ�\�Ȃ̂ő��₵�܂��傤

};
