#include "stdafx.h"
#include "JesseDieState.h"

EnemyState* JesseDieState::Update(EnemyAI* enemy)
{
	// TODO DIE
    return nullptr;
}

void JesseDieState::Enter(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("jesse_die_right", true);
	else
		enemy->ChangeClip("jesse_die_left", true);
}

void JesseDieState::Exit(EnemyAI* enemy)
{
}
