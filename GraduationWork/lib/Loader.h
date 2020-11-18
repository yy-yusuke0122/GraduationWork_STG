#pragma once

#include <unordered_map>
#include <string>

class Loader
{
private:
	Loader()
	{
	}

	~Loader()
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
	/// �f�[�^�ǂݍ���
	/// </summary>
	static void Load();

	/// <summary>
	/// int�^���擾
	/// </summary>
	/// <param name="_key">�֘A�t����ꂽ�L�[</param>
	/// <returns>int�l</returns>
	static int GetInt(const std::string& _key);

	/// <summary>
	/// float�^���擾
	/// </summary>
	/// <param name="_key">�֘A�t����ꂽ�L�[</param>
	/// <returns>float�l</returns>
	static float GetFloat(const std::string& _key);

	/// <summary>
	/// string�^���擾
	/// </summary>
	/// <param name="_key">�֘A�t����ꂽ�L�[</param>
	/// <returns>string�l</returns>
	static std::string GetString(const std::string& _key);

	/// <summary>
	/// �ǂݍ��ݒ���
	/// �񓯊��ǂݍ��݂������ꍇ�A���̊֐��ŏI�����`�F�b�N�ł��܂�
	/// </summary>
	/// <returns>true�F�ǂݍ��ݒ��Afalse�F�ǂݍ��ݏI��</returns>
	static bool IsLoading();//�ǂݍ��ݒ���

	/// <summary>
	/// �ǂݍ��݂��I���܂ő҂�
	/// </summary>
	/// <returns>true�F�����Afalse�F���s</returns>
	static bool Wait();

private:
	static unsigned Loading(LPVOID _param);

private:
	static std::unordered_map<std::string, std::string> info;

	static bool isLoading;

public:
	static bool isAsync;//�񓯊��ǂݍ��݂��s����

};
