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
	/// データ読み込み
	/// </summary>
	static void Load();

	/// <summary>
	/// int型を取得
	/// </summary>
	/// <param name="_key">関連付けられたキー</param>
	/// <returns>int値</returns>
	static int GetInt(const std::string& _key);

	/// <summary>
	/// float型を取得
	/// </summary>
	/// <param name="_key">関連付けられたキー</param>
	/// <returns>float値</returns>
	static float GetFloat(const std::string& _key);

	/// <summary>
	/// string型を取得
	/// </summary>
	/// <param name="_key">関連付けられたキー</param>
	/// <returns>string値</returns>
	static std::string GetString(const std::string& _key);

	/// <summary>
	/// 読み込み中か
	/// 非同期読み込みをした場合、この関数で終了をチェックできます
	/// </summary>
	/// <returns>true：読み込み中、false：読み込み終了</returns>
	static bool IsLoading();//読み込み中か

	/// <summary>
	/// 読み込みが終わるまで待つ
	/// </summary>
	/// <returns>true：成功、false：失敗</returns>
	static bool Wait();

private:
	static unsigned Loading(LPVOID _param);

private:
	static std::unordered_map<std::string, std::string> info;

	static bool isLoading;

public:
	static bool isAsync;//非同期読み込みを行うか

};
