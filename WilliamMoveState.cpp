#include "stdafx.h"
#include "WilliamMoveState.h"
#include "WilliamIdleState.h"
#include "WilliamAttackState.h"

EnemyState * WilliamMoveState::Update(EnemyAI * enemy)
{
	if (enemy->transform->GetX() < enemy->GetPlayerTransform()->GetX())
	{
		if (enemy->enemyinfo->GetDir()== true)
		{
			enemy->ChangeClip("william_move_right", false);
			enemy->enemyinfo->SetDir(false);
		}
	}
	else
	{
		if (enemy->enemyinfo->GetDir()==false)
		{
			enemy->ChangeClip("william_move_left", false);
			enemy->enemyinfo->SetDir(true);
		}
	}
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY()) > 200)
	{
		return new WilliamIdleState();
	}
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY()) < 50)
	{
		return new WilliamAttackState();
	}

	float angle = GetAngle(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY());

	enemy->transform->MoveX(enemy->enemyinfo->GetSpeed() * TIMEMANAGER->getElapsedTime() * cosf(angle));
	enemy->zOrder->MoveZ(enemy->enemyinfo->GetSpeed() * TIMEMANAGER->getElapsedTime() * -sinf(angle));

	return nullptr;
}

void WilliamMoveState::Enter(EnemyAI * enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->ChangeClip("william_move_right", true);
	}
	else
	{
		enemy->ChangeClip("william_move_left", true);
	}
}

void WilliamMoveState::Exit(EnemyAI * enemy)
{
}
