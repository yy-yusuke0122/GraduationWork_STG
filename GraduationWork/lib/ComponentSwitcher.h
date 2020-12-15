#pragma once
#include "StateMachine.h"
#include <map>

class Component;

class ComponentSwitcher {
public:
	ComponentSwitcher();
	~ComponentSwitcher();
	void Update();

	/// <summary>
	/// ステータスマシンをセットする
	/// </summary>
	/// <typeparam name="C">クラス名</typeparam>
	template<class C>
	void SetStateMachine();

	/// <summary>
	/// 現在のステータスを取得する
	/// </summary>
	/// <returns></returns>
	std::string GetState() const;

	/// <summary>
	/// 遷移条件の状態を取得する
	/// </summary>
	/// <param name="_boolName">取得したい遷移条件名</param>
	/// <returns>遷移条件の状態か、存在しない遷移条件を取得しようとした場合false</returns>
	bool GetBool(const std::string& _boolName);

	/// <summary>
	/// 指定した遷移条件に値を設定する
	/// </summary>
	/// <param name="_boolName">設定したい遷移条件名</param>
	/// <param name="_bool">設定したい値</param>
	/// <returns>true:成功, false:存在しない遷移条件</returns>
	bool SetBool(const std::string& _boolName, bool _bool);

	/// <summary>
	/// 対応したステータス時に実行されるコンポーネントを設定する
	/// </summary>
	/// <param name="_stateName">ステータス名</param>
	/// <param name="_comp">実行したコンポーネントのポインター</param>
	/// <returns>true:成功, false:既に設定されているか、対応したステータスが見つからないため失敗</returns>
	bool SetComponent(const std::string& _stateName, Component* _comp);

private:
	/// <summary>
	/// 対応したコンポーネントのアドレスを取得する
	/// </summary>
	/// <param name="_name">ステータス名</param>
	/// <returns>nullptr:対応したステータスが見つからない</returns>
	Component** FindStateComp(const std::string& _name);

	/// <summary>
	/// 現在のステータスに合わせたコンポーネントを有効にする
	/// </summary>
	void ChangeStateComp();

private:
	StateMachine* state;
	Component* currentComp;
	std::string currentState;
	std::map<std::string, Component*> components;
};

template<class C>
inline void ComponentSwitcher::SetStateMachine()
{
	if (state != nullptr)
		return;

	// ステートマシーン生成
	state = new C();
	state->Start();

	// 現在のステータスを設定
	currentState = state->GetState();

	// ステータス名をからmapを初期化
	std::list<std::string> states = state->GetStateAll();
	for (std::list<std::string>::iterator it = states.begin(); it != states.end(); ++it) {
		components.emplace((*it), nullptr);
	}
}
