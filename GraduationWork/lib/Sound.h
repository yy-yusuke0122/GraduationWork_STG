#pragma once

#include <unordered_map>
#include <string>
#include "dxlib/DxLib.h"
#include "AsyncComponent.h"
#include "typedef.h"

enum REVERB
{
	REVERB_DEFAULT,			// デフォルト
	REVERB_GENERIC,			// 一般的な空間
	REVERB_PADDEDCELL,		// 精神病患者室
	REVERB_ROOM,			// 部屋
	REVERB_BATHROOM,		// バスルーム
	REVERB_LIVINGROOM,		// リビングルーム
	REVERB_STONEROOM,		// 石の部屋
	REVERB_AUDITORIUM,		// 講堂
	REVERB_CONCERTHALL,		// コンサートホール
	REVERB_CAVE,			// 洞穴
	REVERB_ARENA,			// 舞台
	REVERB_HANGAR,			// 格納庫
	REVERB_CARPETEDHALLWAY,	// カーペットが敷かれた玄関
	REVERB_HALLWAY,			// 玄関
	REVERB_STONECORRIDOR,	// 石の廊下
	REVERB_ALLEY,			// 裏通り
	REVERB_FOREST,			// 森
	REVERB_CITY,			// 都市
	REVERB_MOUNTAINS,		// 山
	REVERB_QUARRY,			// 採石場
	REVERB_PLAIN,			// 平原
	REVERB_PARKINGLOT,		// 駐車場
	REVERB_SEWERPIPE,		// 下水管
	REVERB_UNDERWATER,		// 水面下
	REVERB_SMALLROOM,		// 小部屋
	REVERB_MEDIUMROOM,		// 中部屋
	REVERB_LARGEROOM,		// 大部屋
	REVERB_MEDIUMHALL,		// 中ホール
	REVERB_LARGEHALL,		// 大ホール
	REVERB_PLATE			// 板
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
	/// サウンドファイル読み込み
	/// </summary>
	/// <param name="_path">ファイルパス</param>
	/// <returns>true：読み込み成功、false：失敗</returns>
	bool Load(const std::string& _path);

	/// <summary>
	/// サウンドファイルを3Dデータとして読み込む
	/// </summary>
	/// <param name="_path">ファイルパス</param>
	/// <returns>true：読み込み成功、false：失敗</returns>
	bool Load3D(const std::string& _path);

	/// <summary>
	/// サウンド再生
	/// </summary>
	/// <returns>true：成功、false：読み込んでいない・ループ再生の重ね掛け</returns>
	bool Play();

	/// <summary>
	/// 再生中のサウンドを止める
	/// </summary>
	/// <returns>true：成功、false：読み込んでいない</returns>
	bool Stop();

	/// <summary>
	/// 読み込んだデータを破棄
	/// </summary>
	void Release();

public://リバーブエフェクト（3D）

	/// <summary>
	/// プリセットからリバーブエフェクトをセット
	/// </summary>
	/// <param name="_preset">セットするリバーブエフェクトの番号</param>
	/// <returns>true：成功、false：失敗</returns>
	bool SetReverb(REVERB _preset);

	/// <summary>
	/// 構造体からリバーブエフェクトをセット
	/// </summary>
	/// <param name="_param">セットするリバーブエフェクト構造体</param>
	/// <returns>true：成功、false：失敗</returns>
	bool SetReverb(SOUND3D_REVERB_PARAM* _param);

	/// <summary>
	/// セットされているリバーブエフェクトを全サウンドに適応
	/// </summary>
	/// <param name="_playSoundOnly">true：再生中のみ、false：全て</param>
	/// <returns>true：成功、false：失敗</returns>
	bool SetReverbAll(bool _playSoundOnly = false);

	/// <summary>
	/// プリセットから全サウンドにリバーブエフェクトをセット
	/// </summary>
	/// <param name="_preset">セットするリバーブエフェクトの番号</param>
	/// <param name="_playSoundOnly">true：再生中のみ、false：全て</param>
	/// <returns>true：成功、false：失敗</returns>
	static bool SetReverbAll(REVERB _preset, bool _playSoundOnly = false);

	/// <summary>
	/// 構造体から全サウンドにリバーブエフェクトをセット
	/// </summary>
	/// <param name="_param">セットするリバーブエフェクト構造体</param>
	/// <param name="_playSoundOnly">true：再生中のみ、false：全て</param>
	/// <returns>true：成功、false：失敗</returns>
	static bool SetReverbAll(SOUND3D_REVERB_PARAM* _param, bool _playSoundOnly = false);

private:
	int CheckAsyncLoading()override;

	void DestroyParam()override;

private:
	void DeleteHandle(std::unordered_map<std::string, INFO>& _info);

	void Set();

public:
	bool isLoop;//ループ再生するか

	int pan;//パン
	int volume;//ボリューム

public://3Dで使用
	float radius;//音が聞こえる距離

	VECTOR3 velocity;//秒速

private:
	bool isAsync;//非同期読み込み中か

	bool is3D;//3D読み込みするか
	bool isLoopPlay;//ループ再生中か

	INFO* soundInfo;//読み込み中のファイル

	std::string path;//読み込み中のファイルパス

	static std::unordered_map<std::string, INFO> loadInfo;//ファイルパスと参照数を関連付ける
	static std::unordered_map<std::string, INFO> load3DInfo;//ファイルパスと参照数を関連付ける（3D用）

};
