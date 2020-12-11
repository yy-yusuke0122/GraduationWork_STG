#pragma once
#include "Component.h"
#include "StateMachine.h"

class StateController : public Component {
public:
	StateController();
	virtual ~StateController();
	void Update() final override;

	/// <summary>
	/// �V�����X�e�[�^�X�Ǘ����Z�b�g����
	/// </summary>
	/// <typeparam name="C">�N���X��</typeparam>
	template<class C>
	void SetStateManager();

	/// <summary>
	/// ���݂̃X�e�[�^�X���擾����
	/// </summary>
	/// <returns></returns>
	std::string GetState() const;

	/// <summary>
	/// �J�ڏ����̏�Ԃ��擾����
	/// </summary>
	/// <param name="_boolName">�擾�������J�ڏ�����</param>
	/// <returns>�J�ڏ����̏�Ԃ��A���݂��Ȃ��J�ڏ������擾���悤�Ƃ����ꍇfalse</returns>
	bool GetBool(const std::string& _boolName);

	/// <summary>
	/// �w�肵���J�ڏ����ɒl��ݒ肷��
	/// </summary>
	/// <param name="_boolName">�ݒ肵�����J�ڏ�����</param>
	/// <param name="_bool">�ݒ肵�����l</param>
	/// <returns>true:����, false:���݂��Ȃ��J�ڏ���</returns>
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
