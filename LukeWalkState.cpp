#include "stdafx.h"
#include "LukeWalkState.h"

EnemyState* LukeWalkState::Update(EnemyAI* enemy)
{
	// TODO WALK
	return nullptr;
}

void LukeWalkState::Enter(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("luke_walk_right", true);
	else
		enemy->ChangeClip("luke_walk_left", true);
}

void LukeWalkState::Exit(EnemyAI* enemy)
{
}
