#include "stdafx.h"
#include "RichardHitState.h"

EnemyState* RichardHitState::Update(EnemyAI* enemy)
{
	// TODO HIT
	return nullptr;
}

void RichardHitState::Enter(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("richard_hit_right", true);
	else
		enemy->ChangeClip("richard_hit_left", true);
}

void RichardHitState::Exit(EnemyAI* enemy)
{
}
