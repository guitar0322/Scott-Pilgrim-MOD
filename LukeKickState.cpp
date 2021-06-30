#include "stdafx.h"
#include "LukeKickState.h"

EnemyState* LukeKickState::Update(EnemyAI* enemy)
{
	// TODO KICK
	return nullptr;
}

void LukeKickState::Enter(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("luke_kick_right", true);
	else
		enemy->ChangeClip("luke_kick_left", true);
}

void LukeKickState::Exit(EnemyAI* enemy)
{
}
