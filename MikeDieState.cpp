#include "stdafx.h"
#include "MikeDieState.h"

EnemyState* MikeDieState::Update(EnemyAI* enemy)
{
    // TODO DIE
    return nullptr;
}

void MikeDieState::Enter(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("mike_die_right", true);
	else
		enemy->ChangeClip("mike_die_left", true);
}

void MikeDieState::Exit(EnemyAI* enemy)
{
}
