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
	/// インスタンスを取得する
	/// </summary>
	/// <returns>インスタンスのポインター</returns>
	static CollideManager* Get();

	/// <summary>
	/// インスタンスを破壊する
	/// </summary>
	/// <returns>true:成功, false:既に破壊されている</returns>
	static bool Destroy();

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="Level">4分木空間の分割レベル(下限1、上限15)</param>
	/// <param name="left">当たり判定を行う範囲の左座標</param>
	/// <param name="top">当たり判定を行う範囲の上座標</param>
	/// <param name="right">当たり判定を行う範囲の右座標</param>
	/// <param name="bottom">当たり判定を行う範囲の下座標</param>
	void Init(unsigned int Level = 8, float left = -1000.0f, float top = -1000.0f, float right = 1000.0f, float bottom = 1000.0f);

	/// <summary>
	/// 当たり判定を確認
	/// </summary>
	void Update();

	/// <summary>
	/// Collider2Dを管理下に追加する
	/// </summary>
	/// <param name="_col">追加したいCollider</param>
	/// <returns>true:成功, false:既に登録されている</returns>
	bool PushCollider2D(Collider2D* _col);

	/// <summary>
	/// Collider3Dを管理下に追加する
	/// </summary>
	/// <param name="_col">追加したいCollider</param>
	/// <returns>true:成功, false:既に登録されている</returns>
	bool PushCollider3D(Collider3D* _col);

	/// <summary>
	/// コライダーを管理下から外す
	/// コライダー削除時に自動で呼ばれるので、直接呼ばないこと
	/// </summary>
	void RemoveCollider2D(Collider2D* _col);

	/// <summary>
	/// コライダーを管理下から外す
	/// コライダー削除時に自動で呼ばれるので、直接呼ばないこと
	/// </summary>
	void RemoveCollider3D(Collider3D* _col);

private:
	CollideManager2D* manager2D;
	CollideManager3D* manager3D;
};