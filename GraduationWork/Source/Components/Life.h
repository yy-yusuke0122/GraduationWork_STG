#pragma once
#include "../../lib/UrLib.h"

class Life : public Component {
public:
	Life();
	~Life();
	void Start();
	void Update();

	/// <summary>
	/// �w�肵���l����hp�����炷
	/// </summary>
	/// <param name="_damage">���炵�����l</param>
	void Damage(float _damage);

	/// <summary>
	/// hp��ݒ肷��
	/// 0���l���������ꍇ��0�A
	/// max���l���傫���ꍇ��max�̒l�ɂȂ�
	/// </summary>
	/// <param name="_hp">�ݒ肵�����l</param>
	void SetHP(float _hp);

	/// <summary>
	/// hp�̍ő�l��ݒ肷��
	/// 0��菬�����ꍇ��0�A
	/// ���݂�hp��菬�����ꍇ�͌��݂�hp��max�Ɠ����l�ɏC�������
	/// </summary>
	/// <param name="_max"></param>
	void SetMaxHP(float _max);

	float hp;
	float max;
};