#pragma once

#include "typedef.h"

class Random
{
private:
	Random()
	{
	}

	~Random()
	{
	}

public:
	/// <summary>
	/// �������l�Z�b�g
	/// </summary>
	/// <returns>true�F�����Afalse�F���s</returns>
	static bool SetSeed(int _seed);

	/// <summary>
	/// ���������_���l�擾
	/// [0, int�ő�l]
	/// </summary>
	/// <returns>���������_���l</returns>
	static int Get();

	/// <summary>
	/// ���������_���l�擾
	/// [0, _max)
	/// </summary>
	/// <param name="_max">�擾���郉���_���l�̍ő�l</param>
	/// <returns>���������_���l<</returns>
	static int Get(int _max);

	/// <summary>
	/// ���������_���l�擾
	/// [_min, _max)
	/// </summary>
	/// <param name="_min">�擾���郉���_���l�̍ŏ��l</param>
	/// <param name="_max">�擾���郉���_���l�̍ő�l</param>
	/// <returns>���������_���l</returns>
	static int Get(int _min, int _max);

	/// <summary>
	/// ���������_�������_���l�擾
	/// [0, 1)
	/// </summary>
	/// <returns>���������_�������_���l</returns>
	static float GetF();

	/// <summary>
	/// ���������_�������_���l�擾
	/// [0, _max)
	/// </summary>
	/// <param name="_max">�擾���郉���_���l�̍ő�l</param>
	/// <returns>���������_�������_���l</returns>
	static float GetF(float _max);

	/// <summary>
	/// ���������_�������_���l�擾
	/// [_min, _max)
	/// </summary>
	/// <param name="_min">�擾���郉���_���l�̍ŏ��l</param>
	/// <param name="_max">�擾���郉���_���l�̍ő�l</param>
	/// <returns>���������_�������_���l</returns>
	static float GetF(float _min, float _max);

	/// <summary>
	/// �����_�������F�擾
	/// </summary>
	/// <returns>�����_�������F</returns>
	static unsigned Color();

	/// <summary>
	/// �����_�������F�擾
	/// </summary>
	/// <returns>�����_�������F</returns>
	static COLOR_F ColorF();

	/// <summary>
	/// �����_��2�����x�N�g���擾
	/// [0, _max)
	/// </summary>
	/// <param name="_max">�擾���郉���_���l�̍ő�l</param>
	/// <returns>�����_��2�����x�N�g��</returns>
	static VECTOR2 Vec2(const VECTOR2& _max);

	/// <summary>
	/// �����_��2�����x�N�g���擾
	/// </summary>
	/// <param name="_min">�擾���郉���_���l�̍ŏ��l</param>
	/// <param name="_max">�擾���郉���_���l�̍ő�l</param>
	/// <returns>�����_��2�����x�N�g��</returns>
	static VECTOR2 Vec2(const VECTOR2& _min, const VECTOR2& _max);

	/// <summary>
	/// �����_��3�����x�N�g���擾
	/// [0, _max)
	/// </summary>
	/// <param name="_max">�擾���郉���_���l�̍ő�l</param>
	/// <returns>�����_��3�����x�N�g��</returns>
	static VECTOR3 Vec3(const VECTOR3& _max);

	/// <summary>
	/// �����_��3�����x�N�g���擾
	/// </summary>
	/// <param name="_min">�擾���郉���_���l�̍ŏ��l</param>
	/// <param name="_max">�擾���郉���_���l�̍ő�l</param>
	/// <returns>�����_��3�����x�N�g��</returns>
	static VECTOR3 Vec3(const VECTOR3& _min, const VECTOR3& _max);

	/// <summary>
	/// �����_���N�H�[�^�j�I���擾
	/// </summary>
	/// <returns>�����_���N�H�[�^�j�I��</returns>
	static Quaternion Rotation();

	/// <summary>
	/// �P�ʉ~���̈�_���擾
	/// </summary>
	/// <returns>�P�ʉ~���̈�_</returns>
	static VECTOR2 InCircle();

	/// <summary>
	/// �P�ʉ~��̈�_���擾
	/// </summary>
	/// <returns>�P�ʉ~��̈�_</returns>
	static VECTOR2 OnCircle();

	/// <summary>
	/// �P�ʋ����̈�_���擾
	/// </summary>
	/// <returns>�P�ʋ����̈�_</returns>
	static VECTOR3 InSphere();

	/// <summary>
	/// �P�ʋ���̈�_���擾
	/// </summary>
	/// <returns>�P�ʋ���̈�_</returns>
	static VECTOR3 OnSphere();

};
