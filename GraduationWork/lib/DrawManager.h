#pragma once

#include <list>
#include <unordered_map>
#include <string>

class Renderer;

class Light;

class DrawManager
{
private:
	DrawManager() {}
	~DrawManager() {}

public:
	/// <summary>
	/// �C���X�^���X�j��
	/// </summary>
	static void Destroy();

	/// <summary>
	/// �o�^���ꂽ�`��I�u�W�F�N�g�̕`��
	/// </summary>
	static void Draw();

	/// <summary>
	/// �`��I�u�W�F�N�g�ǉ�
	/// </summary>
	/// <param name="_p">�ǉ�����`��I�u�W�F�N�g</param>
	static std::list<Renderer*>::iterator AddRenderer(Renderer* _p);

	/// <summary>
	/// �`��I�u�W�F�N�g�ǉ�
	/// </summary>
	/// <param name="_p">�ǉ�����`��I�u�W�F�N�g</param>
	static std::list<Renderer*>::iterator AddRenderer(std::list<Renderer*>::iterator _p);

	/// <summary>
	/// �`��I�u�W�F�N�g�j��
	/// </summary>
	/// <param name="_p">�j������`��I�u�W�F�N�g</param>
	/// <returns>true�F�j���Afalse�F���݂��Ȃ�</returns>
	static bool EraseRenderer(Renderer* _p);

	/// <summary>
	/// ���C�g�I�u�W�F�N�g�ǉ�
	/// </summary>
	static void AddLight(Light* _p);

	/// <summary>
	/// ���C�g�I�u�W�F�N�g�j��
	/// </summary>
	/// <returns>true�F�j���Afalse�F���݂��Ȃ�</returns>
	static bool EraseLight(Light* _p);

private:
	static std::list<Renderer*> rendererList;	//�`�惊�X�g
	static std::list<Light*> lightList;		//���C�g���X�g

//	int shadowHandle;//�V���h�E�}�b�v�̃n���h���FTODO 3�܂Őݒ�\�Ȃ̂ő��₵�܂��傤

};
