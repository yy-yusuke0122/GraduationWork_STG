#pragma once
#include "StateMachine.h"
#include "Component.h"
#include <map>

class ImageRenderer;
class Anim2D;

//class Animator2D : public Component {
//public:
//	Animator2D();
//	virtual ~Animator2D();
//	void Start() final override;
//	void Update() final override;
//
//	/// <summary>
//	/// 新規アニメーションを追加する
//	/// </summary>
//	/// <param name="_animName">アニメーション名</param>
//	/// <param name="_start">開始要素番号(0以上の値)</param>
//	/// <param name="_end">終了要素番号(start以上の値)</param>
//	/// <param name="_animSpeed">アニメーションスピード(0.0f以上の値)</param>
//	/// <param name="_isLoop">ループするか(true : ループする)</param>
//	/// <returns>true:追加成功, false:既に追加されているか、不正な値を渡している</returns>
//	bool AddAnim(std::string _animName, unsigned int _start, unsigned int _end, float _animSpeed = 1.0f, bool _isLoop = true);
//
//	/// <summary>
//	/// 初めに再生されるアニメーションを設定する
//	/// </summary>
//	/// <param name="_animName">アニメーション名</param>
//	/// <returns>true:成功, false:アニメーションが見つからない</returns>
//	bool SetStartAnim(std::string _animName);
//
//	/// <summary>
//	/// アニメーションを取得する
//	/// </summary>
//	/// <param name="_animName">アニメーション名</param>
//	/// <returns>nullptr:取得失敗</returns>
//	Anim2D* GetAnim(std::string _animName);
//
//	/// <summary>
//	/// 現在のアニメーションを取得する
//	/// </summary>
//	/// <returns>nullptr:取得失敗</returns>
//	Anim2D* GetCurrentAnim();
//
//	/// <summary>
//	/// 描画番号を取得する
//	/// </summary>
//	/// <returns>描画する要素番号</returns>
//	int GetDrawNum() const;
//
//	/// <summary>
//	/// 描画番号を設定する
//	/// </summary>
//	/// <param name="_num">描画番号</param>
//	/// <returns>true:成功, false:範囲外の描画番号を指定しているため、エラー</returns>
//	bool SetDrawNum(unsigned int _num);
//
//private:
//	StateController* controller;
//	ImageRenderer* imageRenderer;
//	std::list<Anim2D*> animList;
//	Anim2D* currentAnim;
//	std::string currentAnimName;
//	std::string nextAnimName;
//	unsigned int drawNum;
//};

class Animator2D : public Component {
public:
	Animator2D();
	~Animator2D();
	void Start();
	void Update();

	/// <summary>
	/// ステータスマシンをセットする
	/// </summary>
	/// <param name="_stateMachine">設定するステートマシーン</param>
	/// <returns>true:成功, false:既に設定したステートマシーンが存在する</returns>
	bool SetStateMachine(StateMachine* _stateMachine);

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
	/// ステータスにアニメーションを設定する
	/// </summary>
	/// <param name="_stateName">設定したいアニメーション</param>
	/// <param name="_filePass">アニメーションにしようする画像のファイルパス</param>
	/// <param name="_xdiv">横方向の分割数</param>
	/// <param name="_ydiv">縦方向の分割数</param>
	/// <param name="_allnum">使用する要素数</param>
	/// <param name="_playSpeed">1秒あたりの再生速度</param>
	/// <param name="_start">開始要素番号</param>
	/// <param name="_end">終了要素番号</param>
	/// <param name="_isLoop">ループするかどうか</param>
	/// <returns>設定後のアニメーションのポインター, nullptr:不正な値か、既に設定されている</returns>
	Anim2D* SetAnim(const std::string& _stateName, const std::string& _filePass, unsigned int _xdiv, unsigned int _ydiv, unsigned int _allnum, float _playSpeed = 1.0f, unsigned int _start = 0, unsigned int _end = 0, bool _isLoop = true);

	/// <summary>
	/// ステータスに設定されているアニメーションを取得する
	/// </summary>
	/// <param name="_stateName">ステータス名</param>
	/// <returns>nullptr:取得失敗</returns>
	Anim2D* GetAnim(const std::string& _stateName);

	/// <summary>
	/// 現在のステータスのアニメーションを取得する
	/// </summary>
	/// <returns>nullptr:現在再生されているアニメーションが存在しない</returns>
	Anim2D* GetCurrentAnim();

private:
	/// <summary>
	/// 対応したアニメーションのアドレスを取得する
	/// </summary>
	/// <param name="_name">ステータス名</param>
	/// <returns>nullptr:対応したステータスが見つからない</returns>
	Anim2D** FindStateAnim(const std::string& _name);

	/// <summary>
	/// 現在のステータスに合わせたアニメーションを有効にする
	/// </summary>
	void ChangeStateAnim();

private:
	ImageRenderer* renderer;
	StateMachine* state;
	Anim2D* currentAnim;
	std::string currentState;
	std::map<std::string, Anim2D*> animations;
};
