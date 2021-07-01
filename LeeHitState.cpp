#include "stdafx.h"
#include "LeeHitState.h"

EnemyState* LeeHitState::Update(EnemyAI* enemy)
{
	// TODO HIT
	return nullptr;
}

void LeeHitState::Enter(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("lee_hit_right", true);
	else
		enemy->ChangeClip("lee_hit_left", true);
}

void LeeHitState::Exit(EnemyAI* enemy)
{
}
