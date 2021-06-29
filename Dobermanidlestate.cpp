#include "stdafx.h"
#include "Dobermanidlestate.h"
#include "Dobermanmovestate.h"

EnemyState* DobermanIdleState::Update(EnemyAI* enemy)
{
	int SaveTimer;


	if (GetDistance(enemy->transform->GetX(),enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(),enemy->GetPlayerTransform()->GetY()) < 300)
	{
		if (enemy->transform->GetX() < enemy->GetPlayerTransform()->GetX())
		{
			enemy->enemyinfo->SetDir(false);
		}
		else
		{
			enemy->enemyinfo->SetDir(true);

		}
		return new DobermanMoveState();
	}
	//if (TIMEMANAGER->getWorldTime() >= SaveTimer + 5)
	//{
	//	switch (RND->getInt(3))
	//	{
	//	case 0:
	//		doberman->transform->Move(doberman->GetSpeed()*TIMEMANAGER->getElapsedTime()*cosf(Angle),
	//			doberman->GetSpeed()*TIMEMANAGER->getElapsedTime()*-sinf(Angle));

	//	case 1:

	//	case 2:

	//	default:
	//		break;
	//	}
	//}
	return nullptr;
}

void DobermanIdleState::Enter(EnemyAI * enemy)
{
	_idleTime = 0;
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->ChangeClip("doberman_idle_right", true);
	}
	else
	{
		enemy->ChangeClip("doberman_idle_left", true);
	}
}

void DobermanIdleState::Exit(EnemyAI * enemy)
{
}
