#include "stdafx.h"
#include "MalcolmHitState.h"
#include "MalcolmIdleState.h"


EnemyState * MalcolmHitState::Update(EnemyAI * enemy)
{
	if (enemy->animator->GetEnd() == true)
	{
		return new MalcolmIdleState();
	}

	return nullptr;
}

void MalcolmHitState::Enter(EnemyAI * enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->ChangeClip("malcolm_hit_right", true);
	}
	if (enemy->enemyinfo->GetDir() == true)
	{
		enemy->ChangeClip("malcolm_hit_left", true);
	}
}

void MalcolmHitState::Exit(EnemyAI * enemy)
{
}
