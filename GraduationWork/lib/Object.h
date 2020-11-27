#pragma once
#include <string>

class GameObject;

class Scene;

class Object {
	friend Scene;
	friend GameObject;
public:
	Object();
	virtual ~Object();

	virtual void Start();
	virtual void Update();

	/// <summary>
	/// 名前を取得
	/// </summary>
	/// <returns>名前の文字列</returns>
	std::string GetTypeName() const;

	/// <summary>
	/// 存在しているシーンのポインターを返す
	/// </summary>
	/// <returns>存在しているシーンのポインター</returns>
	virtual Scene* GetScene() const = 0;

	/// <summary>
	/// Objectの有効・無効を取得
	/// </summary>
	/// <returns>Objectの有効状態</returns>
	bool IsActive() const;

	/// <summary>
	/// Objectの有効状態をセットする
	/// </summary>
	/// <param name="_active">有効にするならtrue</param>
	virtual void SetActive(bool _active);

	/// <summary>
	/// Objectの破壊フラグを取得
	/// </summary>
	/// <returns>Objectの破壊フラグ</returns>
	bool IsDestroy() const;

	/// <summary>
	/// Objectの破壊フラグを立てる
	/// </summary>
	void Destroy();

	/// <summary>
	/// シーンのFindGameObjectを呼びます
	/// </summary>
	/// <param name="_tag">オブジェクトのタグ</param>
	/// <returns>SceneのFindGameObject</returns>
	virtual GameObject* FindGameObject(const std::string& _tag);

private:
	std::string className;		// 名前
	bool active;				// 有効状態
	bool isDestroy;				// 破壊フラグ
};
