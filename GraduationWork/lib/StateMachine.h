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
	/// �X�e�[�^�X����S�Ď擾����
	/// </summary>
	/// <returns></returns>
	std::list<std::string> GetStateAll() const;

	/// <summary>
	/// �����̃X�e�[�^�X��ݒ肷��
	/// </summary>
	/// <param name="_stateName">�X�e�[�^�X��</param>
	void SetDefaultState(const std::string& _stateName);

	/// <summary>
	/// �V�����X�e�[�^�X��ǉ�����
	/// </summary>
	/// <param name="_stateName">�X�e�[�^�X�̖���</param>
	void CreateNewState(const std::string& _stateName);

	/// <summary>
	/// �V�����X�e�[�^�X�̑J�ڂ̗�������
	/// </summary>
	/// <param name="_sourceState">�J�ڑO�̃X�e�[�^�X�̖�</param>
	/// <param name="_dirState">�J�ڌ�̃X�e�[�^�X�̖�</param>
	void CreateNewTransDir(const std::string& _sourceState, const std::string& _dirState);

	/// <summary>
	/// �V�����X�e�[�^�X�̑J�ڂ̏��������
	/// </summary>
	/// <param name="_name">�ݒ肵�������O</param>
	void CreateNewTransBool(const std::string& _name);

	/// <summary>
	/// �J�ڂ̗���ɏ�����ݒ肷��
	/// </summary>
	/// <param name="_sourceState">�J�ڑO�̃X�e�[�^�X��</param>
	/// <param name="_dirState">�J�ڌ�̃X�e�[�^�X��</param>
	/// <param name="_boolName">�J�ڂ̏�����</param>
	/// <param name="_enable">�J�ڂ�����</param>
	void SetTransInfo(const std::string& _sourceState, const std::string& _dirState, const std::string& _boolName, bool _enable);

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
	/// ���݂���X�e�[�^�X���ǂ���
	/// </summary>
	/// <param name="_name">�m�F�������X�e�[�^�X��</param>
	/// <returns>���݂��Ă�����true</returns>
	bool isExistState(const std::string& _name);

	/// <summary>
	/// ���݂���J�ڂ̗��ꂩ�ǂ���
	/// </summary>
	/// <param name="_sourceState">�J�ڑO�̃X�e�[�^�X��</param>
	/// <param name="_dirState">�J�ڌ�̃X�e�[�^�X��</param>
	/// <returns>���݂��Ă�����true</returns>
	bool isExistTransDir(const std::string& _sourceState, const std::string& _dirState);

	/// <summary>
	/// ���݂���J�ڏ������ǂ���
	/// </summary>
	/// <param name="_name">�m�F������bool��</param>
	/// <returns>���݂��Ă�����true</returns>
	bool isExistTransBool(const std::string& _name);

private:
	/// <summary>
	/// �X�e�[�^�X�̑J�ڏ����ɗp����bool�^
	/// </summary>
	struct TransBool {
		TransBool(std::string _name) : name(_name), enable(false) {}
		bool enable;		// ���݂̏��
		std::string name;	// bool��
	};

	/// <summary>
	/// �X�e�[�^�X�̑J�ڏ�����ێ�����^
	/// </summary>
	struct TransDirInfo {
		TransDirInfo() { transBool.clear(); transState.clear(); }
		std::vector<TransBool*> transBool;
		std::vector<bool> transState;
		bool IsTranslate();
		bool IsExistInfo(const std::string& _boolName);
	};

	/// <summary>
	/// �X�e�[�^�X�̑J�ڂ̗���������^
	/// </summary>
	struct TransDirection {
		TransDirection(std::string _sourceState, std::string _dirState) : sourceState(_sourceState), dirState(_dirState) {}
		std::string sourceState;	// �J�ڑO�̃X�e�[�^�X��
		std::string dirState;		// �J�ڌ�̃X�e�[�^�X��
		TransDirInfo info;
		bool IsTranslate();
	};

	/// <summary>
	/// �X�e�[�^�X��؂�ւ���K�v�����邩���m�F����
	/// </summary>
	/// <param name="_dir">�J�ڂ���K�v�����鎞�ɑ�������|�C���^�[</param>
	/// <returns>�J�ڂ���K�v������ꍇ��true</returns>
	bool IsTranslate(TransDirection*& _dir);

	std::list<TransBool*> boolList;				// �J�ڂɎg�p����bool�̃��X�g
	std::list<TransDirection*> transDirList;	// �J�ڂ̗�����������̃��X�g

private:
	std::string currentState;					// ���݂̃X�e�[�^�X��
	std::list<std::string> states;				// �X�e�[�^�X���̃��X�g
};