#pragma once
#include "Component.h"
#include "Anim2D.h"
#include <vector>

class ImageRenderer;
class Anim2D;

class Animator2D : public Component {
public:
	Animator2D();
	virtual ~Animator2D();
	void Start();
	void Update() final override;

	/// <summary>
	/// 新規アニメーションを追加する
	/// </summary>
	/// <param name="_start">開始要素番号</param>
	/// <param name="_end">終了要素番号</param>
	/// <param name="_animName">アニメーション名</param>
	/// <param name="_animSpeed">アニメーションスピード</param>
	/// <param name="_isLoop">ループするか(true : ループする)</param>
	/// <returns>true:追加成功, false:既に追加されている</returns>
	bool AddAnim(unsigned int _start, unsigned int _end, std::string _animName, float _animSpeed = 1.0f, bool _isLoop = true);

	/// <summary>
	/// アニメーションを破棄する
	/// </summary>
	/// <param name="_animName">アニメーション名</param>
	/// <returns>true:成功, false:アニメーションが見つからないため失敗</returns>
	bool DeleteAnim(std::string _animName);

	/// <summary>
	/// 初めに再生されるアニメーションを設定する
	/// </summary>
	/// <param name="_animName">アニメーション名</param>
	/// <returns>true:成功, false:アニメーションが見つからない</returns>
	bool SetStartAnim(std::string _animName);

	/// <summary>
	/// アニメーションを取得する
	/// </summary>
	/// <param name="_animName">アニメーション名</param>
	/// <returns>nullptr:取得失敗</returns>
	Anim2D* GetAnim(std::string _animName);

	/// <summary>
	/// 現在のアニメーションを取得する
	/// </summary>
	/// <returns>nullptr:取得失敗</returns>
	Anim2D* GetCurrentAnim();

	/// <summary>
	/// 描画番号を取得する
	/// </summary>
	/// <returns>描画する要素番号</returns>
	int GetDrawNum() const;

	/// <summary>
	/// 描画番号を設定する
	/// </summary>
	/// <param name="_num">描画番号</param>
	/// <returns>true:成功, false:範囲外の描画番号を指定しているため、エラー</returns>
	bool SetDrawNum(unsigned int _num);

	/// <summary>
	/// 指定したアニメーション用bool型の状態を取得
	/// </summary>
	/// <param name="_boolName">アニメーションboolの名前</param>
	/// <returns>アニメーションboolの値</returns>
	bool GetBool(std::string _boolName);

	/// <summary>
	/// 指定したアニメーション用bool型の状態を変更
	/// </summary>
	/// <param name="_boolName">アニメーションboolの名前</param>
	/// <param name="_bool">設定したい値</param>
	void SetBool(std::string _boolName, bool _bool);

	/// <summary>
	/// アニメーション用bool型を新に追加する
	/// </summary>
	/// <param name="_boolName">設定したい名前</param>
	/// <returns>true:成功, false:既に存在している</returns>
	bool CreateBool(std::string _boolName);

	/// <summary>
	/// アニメーション遷移の流れを新たに追加する
	/// </summary>
	/// <param name="_sourceName">遷移前のアニメーション名</param>
	/// <param name="_dirName">遷移先のアニメーション名</param>
	/// <returns>true:成功, false:既に存在している</returns>
	bool CreateTransDirection(std::string _sourceName, std::string _dirName);

	/// <summary>
	/// アニメーション遷移の流れを表す矢印に、遷移条件を追加する
	/// </summary>
	/// <param name="_sourceName">遷移前のアニメーション名</param>
	/// <param name="_dirName">遷移先のアニメーション名</param>
	/// <param name="_boolName">アニメーションboolの名前</param>
	/// <param name="_enable">設定したい値</param>
	/// <returns>true:成功, false:失敗</returns>
	bool AddTransDirInfo(std::string _sourceName, std::string _dirName, std::string _boolName, bool _enable);

private:
	ImageRenderer* imageRenderer;
	std::list<Anim2D*> animList;
	Anim2D* currentAnim;
	std::string currentAnimName;
	std::string nextAnimName;
	float animCount;
	unsigned int drawNum;

	/// <summary>
	/// アニメーションの遷移条件に用いるbool型
	/// </summary>
	struct TransBool {
		TransBool(std::string _boolName) : boolName(_boolName), enable(false) {}
		bool enable;			// 現在の状態
		std::string boolName;	// bool名
	};

	/// <summary>
	/// アニメーションの遷移の条件を保持する型
	/// </summary>
	struct TransDirInfo {
		TransDirInfo() { transBool.clear(); transState.clear(); }
		std::vector<TransBool*> transBool;
		std::vector<bool> transState;
		bool IsTranslate();
	};

	/// <summary>
	/// アニメーションの遷移の流れを示す型
	/// </summary>
	struct TransDirection {
		TransDirection(std::string _sourceName, std::string _dirName) : sourceName(_sourceName), dirName(_dirName) {}
		std::string sourceName;	// 遷移前のアニメーション名
		std::string dirName;	// 遷移後のアニメーション名
		TransDirInfo info;
		bool IsTranslate();
	};

	std::list<TransBool*> boolList;				// 遷移に使用するboolのリスト
	std::list<TransDirection*> transDirList;	// 遷移の流れを示す矢印のリスト

private:
	/// <summary>
	/// アニメーション切り替える
	/// </summary>
	void TransAnimation();

	/// <summary>
	/// アニメーションを切り替える必要があるかを確認する
	/// </summary>
	/// <param name="_dir">遷移する必要がある時に代入されるポインター</param>
	/// <returns>遷移する必要がある場合はtrue</returns>
	bool IsTranslate(TransDirection*& _dir);
};