#include "stdafx.h"
#include "LukeAttack2State.h"

EnemyState* LukeAttack2State::Update(EnemyAI* enemy)
{
    // TODO ATTACK2
    return nullptr;
}

void LukeAttack2State::Enter(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("luke_attack2_right", true);
	else
		enemy->ChangeClip("luke_attack2_left", true);
}

void LukeAttack2State::Exit(EnemyAI* enemy)
{
}
