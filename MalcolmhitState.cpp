#include "stdafx.h"
#include "MalcolmHitState.h"
#include "MalcolmIdleState.h"


EnemyState * MalcolmHitState::Update(EnemyAI * enemy)
{
	_hittime += TIMEMANAGER->getElapsedTime();
	if (_hittime >= 2.0f)
	{
		return new MalcolmHitState();
	}



	return nullptr;
}

void MalcolmHitState::Enter(EnemyAI * enemy)
{
	_hittime = 0;
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
