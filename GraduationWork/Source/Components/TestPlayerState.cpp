#include "TestPlayerState.h"

TestPlayerState::TestPlayerState()
{
}

TestPlayerState::~TestPlayerState()
{
}

void TestPlayerState::Start()
{
	// ステータスを新規作成
	CreateNewState("Idle");
	CreateNewState("Move");
	CreateNewState("Attack");

	// ステータスの遷移の流れを作成
	CreateNewTransDir("Idle", "Move");
	CreateNewTransDir("Idle", "Attack");
	CreateNewTransDir("Move", "Idle");
	CreateNewTransDir("Move", "Attack");
	CreateNewTransDir("Attack", "Idle");

	// 遷移に使う条件を作成
	CreateNewTransBool("isMove");
	CreateNewTransBool("isAttack");

	// ステータスの遷移の流れに遷移の条件を設定
	SetTransInfo("Idle", "Move", "isMove", true);
	SetTransInfo("Idle", "Attack", "isAttack", true);
	SetTransInfo("Move", "Idle", "isMove", false);
	SetTransInfo("Move", "Attack", "isAttack", true);
	SetTransInfo("Attack", "Idle", "isAttack", false);

	// 初期ステータスを設定
	SetDefaultState("Idle");
}
