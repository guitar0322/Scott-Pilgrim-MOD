#include "stdafx.h"
#include "LukeHitState.h"

EnemyState* LukeHitState::Update(EnemyAI* enemy)
{
	// TODO HIT
	return nullptr;
}

void LukeHitState::Enter(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("luke_hit_right", true);
	else
		enemy->ChangeClip("luke_hit_left", true);
}

void LukeHitState::Exit(EnemyAI* enemy)
{
}
