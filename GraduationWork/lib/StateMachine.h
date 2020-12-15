#pragma once
#include <string>
#include <vector>
#include <list>

class TransBool;

class StateMachine {
public:
	StateMachine();
	~StateMachine();
	virtual void Start();
	void Update();

	std::string GetState() const;

	/// <summary>
	/// ステータス名を全て取得する
	/// </summary>
	/// <returns></returns>
	std::list<std::string> GetStateAll() const;

	/// <summary>
	/// 初期のステータスを設定する
	/// </summary>
	/// <param name="_stateName">ステータス名</param>
	void SetDefaultState(const std::string& _stateName);

	/// <summary>
	/// 新しくステータスを追加する
	/// </summary>
	/// <param name="_stateName">ステータスの名称</param>
	void CreateNewState(const std::string& _stateName);

	/// <summary>
	/// 新しくステータスの遷移の流れを作る
	/// </summary>
	/// <param name="_sourceState">遷移前のステータスの名</param>
	/// <param name="_dirState">遷移後のステータスの名</param>
	void CreateNewTransDir(const std::string& _sourceState, const std::string& _dirState);

	/// <summary>
	/// 新しくステータスの遷移の条件を作る
	/// </summary>
	/// <param name="_name">設定したい名前</param>
	void CreateNewTransBool(const std::string& _name);

	/// <summary>
	/// 遷移の流れに条件を設定する
	/// </summary>
	/// <param name="_sourceState">遷移前のステータス名</param>
	/// <param name="_dirState">遷移後のステータス名</param>
	/// <param name="_boolName">遷移の条件名</param>
	/// <param name="_enable">遷移する状態</param>
	void SetTransInfo(const std::string& _sourceState, const std::string& _dirState, const std::string& _boolName, bool _enable);

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
	/// 存在するステータスかどうか
	/// </summary>
	/// <param name="_name">確認したいステータス名</param>
	/// <returns>存在していたらtrue</returns>
	bool isExistState(const std::string& _name);

	/// <summary>
	/// 存在する遷移の流れかどうか
	/// </summary>
	/// <param name="_sourceState">遷移前のステータス名</param>
	/// <param name="_dirState">遷移後のステータス名</param>
	/// <returns>存在していたらtrue</returns>
	bool isExistTransDir(const std::string& _sourceState, const std::string& _dirState);

	/// <summary>
	/// 存在する遷移条件かどうか
	/// </summary>
	/// <param name="_name">確認したいbool名</param>
	/// <returns>存在していたらtrue</returns>
	bool isExistTransBool(const std::string& _name);

private:
	/// <summary>
	/// ステータスの遷移条件に用いるbool型
	/// </summary>
	struct TransBool {
		TransBool(std::string _name) : name(_name), enable(false) {}
		bool enable;		// 現在の状態
		std::string name;	// bool名
	};

	/// <summary>
	/// ステータスの遷移条件を保持する型
	/// </summary>
	struct TransDirInfo {
		TransDirInfo() { transBool.clear(); transState.clear(); }
		std::vector<TransBool*> transBool;
		std::vector<bool> transState;
		bool IsTranslate();
		bool IsExistInfo(const std::string& _boolName);
	};

	/// <summary>
	/// ステータスの遷移の流れを示す型
	/// </summary>
	struct TransDirection {
		TransDirection(std::string _sourceState, std::string _dirState) : sourceState(_sourceState), dirState(_dirState) {}
		std::string sourceState;	// 遷移前のステータス名
		std::string dirState;		// 遷移後のステータス名
		TransDirInfo info;
		bool IsTranslate();
	};

	/// <summary>
	/// ステータスを切り替える必要があるかを確認する
	/// </summary>
	/// <param name="_dir">遷移する必要がある時に代入されるポインター</param>
	/// <returns>遷移する必要がある場合はtrue</returns>
	bool IsTranslate(TransDirection*& _dir);

	std::list<TransBool*> boolList;				// 遷移に使用するboolのリスト
	std::list<TransDirection*> transDirList;	// 遷移の流れを示す矢印のリスト

private:
	std::string currentState;					// 現在のステータス名
	std::list<std::string> states;				// ステータス名のリスト
};