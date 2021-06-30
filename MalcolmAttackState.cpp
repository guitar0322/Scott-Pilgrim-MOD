#include "stdafx.h"
#include "MalcolmAttackState.h"
#include "MalcolmIdleState.h"
#include "MalcolmhitState.h"

EnemyState * MalcolmAttackState::Update(EnemyAI * enemy)
{
	_attackTime += TIMEMANAGER->getElapsedTime();
	if (_attackTime >= 2.0f)
	{
		return new MalcolmhitState();
	}
	return nullptr;
}

void MalcolmAttackState::Enter(EnemyAI * enemy)
{
	_attackTime = 0;
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->ChangeClip("malcolm_attack_right", true);
	}
	else
	{
		enemy->ChangeClip("malcolm_attack_left", true);
	}
}

void MalcolmAttackState::Exit(EnemyAI * enemy)
{
}
