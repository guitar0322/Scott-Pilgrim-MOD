#include "stdafx.h"
#include "Dobermanmovestate.h"
#include "Dobermanidlestate.h"
#include "DobermanAttackstate.h"
#include "Enemy.h"

EnemyState * DobermanMoveState::Update(EnemyAI* enemy)
{
	_delaytime += TIMEMANAGER->getElapsedTime();


	if (enemy->transform->GetX() < enemy->GetPlayerTransform()->GetX())
	{
		if (enemy->enemyinfo->GetDir()==true)
		{
			enemy->ChangeClip("doberman_move_right", false);
			enemy->enemyinfo->SetDir(false);
		}
	}
	else
	{
		if (enemy->enemyinfo->GetDir() == false)
		{
			enemy->ChangeClip("doberman_move_left", false);
			enemy->enemyinfo->SetDir(true);
		}
	}
	if (GetDistance(enemy->transform->GetX(),enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(),enemy->GetPlayerTransform()->GetY())>300) // idle의 반응 거리와 같아야함 다르게 설정하면 서로 표현을 반경때문에 버벅거림.
	{
		return new DobermanIdleState();
	}
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY()) < 50)
	{
		return new DobermanAttackState();
	}


	float angle = GetAngle(enemy->transform->GetX(), enemy->transform->GetY(), 
				enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY());

	enemy->transform->Move(enemy->enemyinfo->GetSpeed()*TIMEMANAGER->getElapsedTime()*cosf(angle),
		enemy->enemyinfo->GetSpeed()*TIMEMANAGER->getElapsedTime()*-sinf(angle));

	return nullptr;
}

void DobermanMoveState::Enter(EnemyAI * doberman)
{
	if (doberman->enemyinfo->GetDir() == false)
	{
		doberman->ChangeClip("doberman_move_right", true);
	}
	else
	{
		doberman->ChangeClip("doberman_move_left", true);
	}
}

void DobermanMoveState::Exit(EnemyAI * doberman)
{
}
