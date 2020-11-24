#pragma once
#include "../../lib/UrLib.h"

class Life : public Component {
public:
	Life();
	~Life();
	void Start();
	void Update();

	/// <summary>
	/// 指定した値だけhpを減らす
	/// </summary>
	/// <param name="_damage">減らしたい値</param>
	void Damage(float _damage);

	/// <summary>
	/// hpを設定する
	/// 0より値が小さい場合は0、
	/// maxより値が大きい場合はmaxの値になる
	/// </summary>
	/// <param name="_hp">設定したい値</param>
	void SetHP(float _hp);

	/// <summary>
	/// hpの最大値を設定する
	/// 0より小さい場合は0、
	/// 現在のhpより小さい場合は現在のhpがmaxと同じ値に修正される
	/// </summary>
	/// <param name="_max"></param>
	void SetMaxHP(float _max);

	float hp;
	float max;
};