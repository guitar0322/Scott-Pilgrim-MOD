#include "stdafx.h"
#include "MalcolmhitState.h"


EnemyState * MalcolmhitState::Update(EnemyAI * enemy)
{
	_hittime += TIMEMANAGER->getElapsedTime();
	if (_hittime >= 2.0f)
	{
		return new MalcolmhitState();
	}



	return nullptr;
}

void MalcolmhitState::Enter(EnemyAI * enemy)
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

void MalcolmhitState::Exit(EnemyAI * enemy)
{
}
