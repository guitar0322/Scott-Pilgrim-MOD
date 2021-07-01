#include "stdafx.h"
#include "RichardDieState.h"

EnemyState* RichardDieState::Update(EnemyAI* enemy)
{
	// TODO DIE
    return nullptr;
}

void RichardDieState::Enter(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("richard_die_right", true);
	else
		enemy->ChangeClip("richard_die_left", true);
}

void RichardDieState::Exit(EnemyAI* enemy)
{
}