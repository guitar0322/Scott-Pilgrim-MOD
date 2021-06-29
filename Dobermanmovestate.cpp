#include "stdafx.h"
#include "DobermanMoveState.h"
#include "DobermanIdleState.h"
#include "DobermanAttackState.h"
#include "Enemy.h"

EnemyState * DobermanMoveState::Update(EnemyAI* enemy)
{
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
		enemy->GetPlayerTransform()->GetX(),enemy->GetPlayerTransform()->GetY())>300) // idle�� ���� �Ÿ��� ���ƾ��� �ٸ��� �����ϸ� ���� ǥ���� �ݰ涧���� �����Ÿ�.
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
