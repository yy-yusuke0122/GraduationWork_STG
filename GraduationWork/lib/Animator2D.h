#pragma once
#include "Component.h"
#include "Anim2D.h"
#include <vector>

class ImageRenderer;
class Anim2D;
class StateController;

class Animator2D : public Component {
public:
	Animator2D();
	virtual ~Animator2D();
	/*void Start() final override;
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

private:
	StateController* controller;
	ImageRenderer* imageRenderer;
	std::list<Anim2D*> animList;
	Anim2D* currentAnim;
	std::string currentAnimName;
	std::string nextAnimName;
	unsigned int drawNum;*/
};