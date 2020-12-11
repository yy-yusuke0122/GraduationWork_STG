#pragma once
#include "Component.h"
#include "StateMachine.h"

class StateController : public Component {
public:
	StateController();
	virtual ~StateController();
	void Update() final override;

	/// <summary>
	/// 新しいステータス管理をセットする
	/// </summary>
	/// <typeparam name="C">クラス名</typeparam>
	template<class C>
	void SetStateManager();

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

private:
	StateMachine* state;
};

template<class C>
inline void StateController::SetStateManager()
{
	if (state != nullptr)
		delete state;

	state = new C();
	state->Start();
}
