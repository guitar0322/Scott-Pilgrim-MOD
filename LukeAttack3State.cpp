#include "stdafx.h"
#include "LukeAttack3State.h"

EnemyState* LukeAttack3State::Update(EnemyAI* enemy)
{
    // TODO ATTACK3
    return nullptr;
}

void LukeAttack3State::Enter(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("luke_attack3_right", true);
	else
		enemy->ChangeClip("luke_attack3_left", true);
}

void LukeAttack3State::Exit(EnemyAI* enemy)
{
}
