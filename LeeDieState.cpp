#include "stdafx.h"
#include "LeeDieState.h"

EnemyState* LeeDieState::Update(EnemyAI* enemy)
{
	// TODO DIE
    return nullptr;
}

void LeeDieState::Enter(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("lee_die_right", true);
	else
		enemy->ChangeClip("lee_die_left", true);
}

void LeeDieState::Exit(EnemyAI* enemy)
{
}
