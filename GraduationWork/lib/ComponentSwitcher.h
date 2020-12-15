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
	/// �X�e�[�^�X�}�V�����Z�b�g����
	/// </summary>
	/// <typeparam name="C">�N���X��</typeparam>
	template<class C>
	void SetStateMachine();

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

	/// <summary>
	/// �Ή������X�e�[�^�X���Ɏ��s�����R���|�[�l���g��ݒ肷��
	/// </summary>
	/// <param name="_stateName">�X�e�[�^�X��</param>
	/// <param name="_comp">���s�����R���|�[�l���g�̃|�C���^�[</param>
	/// <returns>true:����, false:���ɐݒ肳��Ă��邩�A�Ή������X�e�[�^�X��������Ȃ����ߎ��s</returns>
	bool SetComponent(const std::string& _stateName, Component* _comp);

private:
	/// <summary>
	/// �Ή������R���|�[�l���g�̃A�h���X���擾����
	/// </summary>
	/// <param name="_name">�X�e�[�^�X��</param>
	/// <returns>nullptr:�Ή������X�e�[�^�X��������Ȃ�</returns>
	Component** FindStateComp(const std::string& _name);

	/// <summary>
	/// ���݂̃X�e�[�^�X�ɍ��킹���R���|�[�l���g��L���ɂ���
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

	// �X�e�[�g�}�V�[������
	state = new C();
	state->Start();

	// ���݂̃X�e�[�^�X��ݒ�
	currentState = state->GetState();

	// �X�e�[�^�X��������map��������
	std::list<std::string> states = state->GetStateAll();
	for (std::list<std::string>::iterator it = states.begin(); it != states.end(); ++it) {
		components.emplace((*it), nullptr);
	}
}
