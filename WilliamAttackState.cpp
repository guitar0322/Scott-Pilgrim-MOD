#include "stdafx.h"
#include "WilliamAttackState.h"
#include "WilliamIdleState.h"

EnemyState * WilliamAttackState::Update(EnemyAI * enemy)
{
	_attackTime += TIMEMANAGER->getElapsedTime();
	if (_attackTime >= 2.0f)
	{
		return new WilliamIdleState();
	}
	return nullptr;
}

void WilliamAttackState::Enter(EnemyAI * enemy)
{
	_attackTime = 0;
	if (enemy->enemyinfo->GetDir()==false)
	{
		enemy->ChangeClip("william_attack_right",true);
	}
	else
	{
		enemy->ChangeClip("william_attack_left",true);
	}
}

void WilliamAttackState::Exit(EnemyAI * enemy)
{
}
