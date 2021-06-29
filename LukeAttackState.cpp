#include "stdafx.h"
#include "Enemy.h"
#include "LukeIdleState.h"
#include "LukeAttackState.h"

EnemyState* LukeAttackState::Update(EnemyAI* enemy)
{
	_attackTime += TIMEMANAGER->getElapsedTime();
	if (_attackTime >= 1.0f)
		return new LukeIdleState();

	return nullptr;
}

void LukeAttackState::Enter(EnemyAI* enemy)
{
	_attackTime = 0;
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("lee_attack1_right", true);
	else
		enemy->ChangeClip("lee_attack1_left", true);
}

void LukeAttackState::Exit(EnemyAI* enemy)
{
}
