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
	/// データ全削除
	/// </summary>
	static void DeleteAll();

	/// <summary>
	/// キーに関連したデータ削除
	/// </summary>
	/// <param name="_key">削除するデータと関連したキー</param>
	static void DeleteKey(const std::string& _key);

	/// <summary>
	/// キーが存在するか
	/// </summary>
	/// <param name="_key">検索するキー</param>
	/// <returns>true：存在する、false：存続しない</returns>
	static bool HasKey(const std::string& _key);

	/// <summary>
	/// データを保存
	/// </summary>
	static void Save();

	/// <summary>
	/// int型をセット
	/// </summary>
	/// <param name="_key">関連付けるキー</param>
	/// <param name="_data">データ</param>
	/// <returns>true：成功、false：失敗</returns>
	static bool SetInt(const std::string& _key, int _data);

	/// <summary>
	/// float型をセット
	/// </summary>
	/// <param name="_key">関連付けるキー</param>
	/// <param name="_data">データ</param>
	/// <returns>true：成功、false：失敗</returns>
	static bool SetFloat(const std::string& _key, float _data);

	/// <summary>
	/// string型をセット
	/// </summary>
	/// <param name="_key">関連付けるキー</param>
	/// <param name="_data">データ</param>
	/// <returns>true：成功、false：失敗</returns>
	static bool SetString(const std::string& _key, const std::string& _data);

	/// <summary>
	/// 保存中か
	/// 非同期保存をした場合、この関数で終了をチェックできます
	/// </summary>
	/// <returns>true：読み込み中、false：読み込み終了</returns>
	static bool IsSaving();

	/// <summary>
	/// 保存が終わるまで待つ
	/// </summary>
	/// <returns>true：成功、false：失敗</returns>
	static bool Wait();

private:
	static unsigned Saving(LPVOID _param);

private:
	static std::unordered_map<std::string, std::string> info;

	static bool isSaving;

public:
	static bool isAsync;//非同期保存を行うか

};
