#pragma once

#include <unordered_map>
#include <string>
#include "dxlib/DxLib.h"
#include "AsyncComponent.h"
#include "typedef.h"

enum REVERB
{
	REVERB_DEFAULT,			// �f�t�H���g
	REVERB_GENERIC,			// ��ʓI�ȋ��
	REVERB_PADDEDCELL,		// ���_�a���Ҏ�
	REVERB_ROOM,			// ����
	REVERB_BATHROOM,		// �o�X���[��
	REVERB_LIVINGROOM,		// ���r���O���[��
	REVERB_STONEROOM,		// �΂̕���
	REVERB_AUDITORIUM,		// �u��
	REVERB_CONCERTHALL,		// �R���T�[�g�z�[��
	REVERB_CAVE,			// ����
	REVERB_ARENA,			// ����
	REVERB_HANGAR,			// �i�[��
	REVERB_CARPETEDHALLWAY,	// �J�[�y�b�g���~���ꂽ����
	REVERB_HALLWAY,			// ����
	REVERB_STONECORRIDOR,	// �΂̘L��
	REVERB_ALLEY,			// ���ʂ�
	REVERB_FOREST,			// �X
	REVERB_CITY,			// �s�s
	REVERB_MOUNTAINS,		// �R
	REVERB_QUARRY,			// �̐Ώ�
	REVERB_PLAIN,			// ����
	REVERB_PARKINGLOT,		// ���ԏ�
	REVERB_SEWERPIPE,		// ������
	REVERB_UNDERWATER,		// ���ʉ�
	REVERB_SMALLROOM,		// ������
	REVERB_MEDIUMROOM,		// ������
	REVERB_LARGEROOM,		// �啔��
	REVERB_MEDIUMHALL,		// ���z�[��
	REVERB_LARGEHALL,		// ��z�[��
	REVERB_PLATE			// ��
};

class Sound :public AsyncComponent
{
	struct INFO
	{
		INFO() :count(1) {}
		int handle;
		int count;
	};

public:
	Sound() :
		isLoop(false), is3D(false), isLoopPlay(false), soundInfo(nullptr),
		pan(0), volume(128), radius(100.f)
	{
	}

	~Sound();

	void Update()override;

	/// <summary>
	/// �T�E���h�t�@�C���ǂݍ���
	/// </summary>
	/// <param name="_path">�t�@�C���p�X</param>
	/// <returns>true�F�ǂݍ��ݐ����Afalse�F���s</returns>
	bool Load(const std::string& _path);

	/// <summary>
	/// �T�E���h�t�@�C����3D�f�[�^�Ƃ��ēǂݍ���
	/// </summary>
	/// <param name="_path">�t�@�C���p�X</param>
	/// <returns>true�F�ǂݍ��ݐ����Afalse�F���s</returns>
	bool Load3D(const std::string& _path);

	/// <summary>
	/// �T�E���h�Đ�
	/// </summary>
	/// <returns>true�F�����Afalse�F�ǂݍ���ł��Ȃ��E���[�v�Đ��̏d�ˊ|��</returns>
	bool Play();

	/// <summary>
	/// �Đ����̃T�E���h���~�߂�
	/// </summary>
	/// <returns>true�F�����Afalse�F�ǂݍ���ł��Ȃ�</returns>
	bool Stop();

	/// <summary>
	/// �ǂݍ��񂾃f�[�^��j��
	/// </summary>
	void Release();

public://���o�[�u�G�t�F�N�g�i3D�j

	/// <summary>
	/// �v���Z�b�g���烊�o�[�u�G�t�F�N�g���Z�b�g
	/// </summary>
	/// <param name="_preset">�Z�b�g���郊�o�[�u�G�t�F�N�g�̔ԍ�</param>
	/// <returns>true�F�����Afalse�F���s</returns>
	bool SetReverb(REVERB _preset);

	/// <summary>
	/// �\���̂��烊�o�[�u�G�t�F�N�g���Z�b�g
	/// </summary>
	/// <param name="_param">�Z�b�g���郊�o�[�u�G�t�F�N�g�\����</param>
	/// <returns>true�F�����Afalse�F���s</returns>
	bool SetReverb(SOUND3D_REVERB_PARAM* _param);

	/// <summary>
	/// �Z�b�g����Ă��郊�o�[�u�G�t�F�N�g��S�T�E���h�ɓK��
	/// </summary>
	/// <param name="_playSoundOnly">true�F�Đ����̂݁Afalse�F�S��</param>
	/// <returns>true�F�����Afalse�F���s</returns>
	bool SetReverbAll(bool _playSoundOnly = false);

	/// <summary>
	/// �v���Z�b�g����S�T�E���h�Ƀ��o�[�u�G�t�F�N�g���Z�b�g
	/// </summary>
	/// <param name="_preset">�Z�b�g���郊�o�[�u�G�t�F�N�g�̔ԍ�</param>
	/// <param name="_playSoundOnly">true�F�Đ����̂݁Afalse�F�S��</param>
	/// <returns>true�F�����Afalse�F���s</returns>
	static bool SetReverbAll(REVERB _preset, bool _playSoundOnly = false);

	/// <summary>
	/// �\���̂���S�T�E���h�Ƀ��o�[�u�G�t�F�N�g���Z�b�g
	/// </summary>
	/// <param name="_param">�Z�b�g���郊�o�[�u�G�t�F�N�g�\����</param>
	/// <param name="_playSoundOnly">true�F�Đ����̂݁Afalse�F�S��</param>
	/// <returns>true�F�����Afalse�F���s</returns>
	static bool SetReverbAll(SOUND3D_REVERB_PARAM* _param, bool _playSoundOnly = false);

private:
	int CheckAsyncLoading()override;

	void DestroyParam()override;

private:
	void DeleteHandle(std::unordered_map<std::string, INFO>& _info);

	void Set();

public:
	bool isLoop;//���[�v�Đ����邩

	int pan;//�p��
	int volume;//�{�����[��

public://3D�Ŏg�p
	float radius;//�����������鋗��

	VECTOR3 velocity;//�b��

private:
	bool isAsync;//�񓯊��ǂݍ��ݒ���

	bool is3D;//3D�ǂݍ��݂��邩
	bool isLoopPlay;//���[�v�Đ�����

	INFO* soundInfo;//�ǂݍ��ݒ��̃t�@�C��

	std::string path;//�ǂݍ��ݒ��̃t�@�C���p�X

	static std::unordered_map<std::string, INFO> loadInfo;//�t�@�C���p�X�ƎQ�Ɛ����֘A�t����
	static std::unordered_map<std::string, INFO> load3DInfo;//�t�@�C���p�X�ƎQ�Ɛ����֘A�t����i3D�p�j

};
