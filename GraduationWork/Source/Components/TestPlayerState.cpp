#include "TestPlayerState.h"

TestPlayerState::TestPlayerState()
{
}

TestPlayerState::~TestPlayerState()
{
}

void TestPlayerState::Start()
{
	// �X�e�[�^�X��V�K�쐬
	CreateNewState("Idle");
	CreateNewState("Move");
	CreateNewState("Attack");

	// �X�e�[�^�X�̑J�ڂ̗�����쐬
	CreateNewTransDir("Idle", "Move");
	CreateNewTransDir("Idle", "Attack");
	CreateNewTransDir("Move", "Idle");
	CreateNewTransDir("Move", "Attack");
	CreateNewTransDir("Attack", "Idle");

	// �J�ڂɎg���������쐬
	CreateNewTransBool("isMove");
	CreateNewTransBool("isAttack");

	// �X�e�[�^�X�̑J�ڂ̗���ɑJ�ڂ̏�����ݒ�
	SetTransInfo("Idle", "Move", "isMove", true);
	SetTransInfo("Idle", "Attack", "isAttack", true);
	SetTransInfo("Move", "Idle", "isMove", false);
	SetTransInfo("Move", "Attack", "isAttack", true);
	SetTransInfo("Attack", "Idle", "isAttack", false);

	// �����X�e�[�^�X��ݒ�
	SetDefaultState("Idle");
}
