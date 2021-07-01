#include "stdafx.h"
#include "MikeHitState.h"

EnemyState* MikeHitState::Update(EnemyAI* enemy)
{
	// TODO HIT
    return nullptr;
}

void MikeHitState::Enter(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("mike_hit_right", true);
	else
		enemy->ChangeClip("mike_hit_left", true);
}

void MikeHitState::Exit(EnemyAI* enemy)
{
}
