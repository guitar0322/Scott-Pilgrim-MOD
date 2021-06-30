#include "stdafx.h"
#include "Enemy.h"
#include "LukeIdleState.h"
#include "LukeAttack1State.h"

EnemyState* LukeAttack1State::Update(EnemyAI* enemy)
{
	_attackTime += TIMEMANAGER->getElapsedTime();
	if (_attackTime >= 1.0f)
		return new LukeIdleState();

	return nullptr;
}

void LukeAttack1State::Enter(EnemyAI* enemy)
{
	_attackTime = 0;
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("luke_attack1_right", true);
	else
		enemy->ChangeClip("luke_attack1_left", true);
}

void LukeAttack1State::Exit(EnemyAI* enemy)
{
}
