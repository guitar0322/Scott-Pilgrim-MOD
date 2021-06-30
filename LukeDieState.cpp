#include "stdafx.h"
#include "LukeDieState.h"

EnemyState* LukeDieState::Update(EnemyAI* enemy)
{
	// TODO DIE
	return nullptr;
}

void LukeDieState::Enter(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("luke_die_right", true);
	else
		enemy->ChangeClip("luke_die_left", true);
}

void LukeDieState::Exit(EnemyAI* enemy)
{
}
