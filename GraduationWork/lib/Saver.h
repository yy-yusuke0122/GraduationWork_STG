#pragma once

#include <unordered_map>

class Saver
{
private:
	Saver()
	{
	}

	~Saver()
	{
	}

public:
	/// <summary>
	/// �f�[�^�S�폜
	/// </summary>
	static void DeleteAll();

	/// <summary>
	/// �L�[�Ɋ֘A�����f�[�^�폜
	/// </summary>
	/// <param name="_key">�폜����f�[�^�Ɗ֘A�����L�[</param>
	static void DeleteKey(const std::string& _key);

	/// <summary>
	/// �L�[�����݂��邩
	/// </summary>
	/// <param name="_key">��������L�[</param>
	/// <returns>true�F���݂���Afalse�F�������Ȃ�</returns>
	static bool HasKey(const std::string& _key);

	/// <summary>
	/// �f�[�^��ۑ�
	/// </summary>
	static void Save();

	/// <summary>
	/// int�^���Z�b�g
	/// </summary>
	/// <param name="_key">�֘A�t����L�[</param>
	/// <param name="_data">�f�[�^</param>
	/// <returns>true�F�����Afalse�F���s</returns>
	static bool SetInt(const std::string& _key, int _data);

	/// <summary>
	/// float�^���Z�b�g
	/// </summary>
	/// <param name="_key">�֘A�t����L�[</param>
	/// <param name="_data">�f�[�^</param>
	/// <returns>true�F�����Afalse�F���s</returns>
	static bool SetFloat(const std::string& _key, float _data);

	/// <summary>
	/// string�^���Z�b�g
	/// </summary>
	/// <param name="_key">�֘A�t����L�[</param>
	/// <param name="_data">�f�[�^</param>
	/// <returns>true�F�����Afalse�F���s</returns>
	static bool SetString(const std::string& _key, const std::string& _data);

	/// <summary>
	/// �ۑ�����
	/// �񓯊��ۑ��������ꍇ�A���̊֐��ŏI�����`�F�b�N�ł��܂�
	/// </summary>
	/// <returns>true�F�ǂݍ��ݒ��Afalse�F�ǂݍ��ݏI��</returns>
	static bool IsSaving();

	/// <summary>
	/// �ۑ����I���܂ő҂�
	/// </summary>
	/// <returns>true�F�����Afalse�F���s</returns>
	static bool Wait();

private:
	static unsigned Saving(LPVOID _param);

private:
	static std::unordered_map<std::string, std::string> info;

	static bool isSaving;

public:
	static bool isAsync;//�񓯊��ۑ����s����

};
