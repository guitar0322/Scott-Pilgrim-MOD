#include "stdafx.h"
#include "LukeIdleState.h"
#include "LukeWalkState.h"
#include "LukeRunState.h"
#include "LukeAttack1State.h"

EnemyState* LukeWalkState::Update(EnemyAI* enemy)
{
	if (enemy->transform->GetX() < enemy->GetPlayerTransform()->GetX())
	{
		if (enemy->enemyinfo->GetDir() == true)
		{
			enemy->ChangeClip("luke_walk_right", false);
			enemy->enemyinfo->SetDir(false);
		}
	}
	else
	{
		if (enemy->enemyinfo->GetDir() == false)
		{
			enemy->ChangeClip("luke_walk_left", false);
			enemy->enemyinfo->SetDir(true);
		}
	}

	/* PATROL-MOVE */
	_moveStartTime += TIMEMANAGER->getElapsedTime();
	//if (_isPatrol)
	//{
		enemy->transform->MoveX(enemy->enemyinfo->GetSpeed() * TIMEMANAGER->getElapsedTime() * cosf(_angle));
		enemy->zOrder->MoveZ(enemy->enemyinfo->GetSpeed() * TIMEMANAGER->getElapsedTime() * -sinf(_angle));
	//}
	//else
	//{
	//	float rndAngle = GetAngle(enemy->transform->GetX(), enemy->transform->GetY(), enemy->patrolPoint.first, enemy->patrolPoint.second);
	//	enemy->transform->MoveX(enemy->enemyinfo->GetSpeed() * TIMEMANAGER->getElapsedTime() * cosf(rndAngle));
	//	enemy->zOrder->MoveZ(enemy->enemyinfo->GetSpeed() * TIMEMANAGER->getElapsedTime() * -sinf(rndAngle));
	//
	//}


	/* PATROL�� ������ ��Ҹ� ������ �� ���� �� */
	if (_moveStartTime >= _moveMaxTime)
	{
		_moveStartTime = 0;
		return new LukeIdleState();
	}

	/* PATROL�� ������ ��� ��ó ������ */
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(), enemy->patrolPoint.first, enemy->patrolPoint.second) < 1.0f)
	{
		return new LukeIdleState();
	}

	/* IDLE ���� �� ���� �ȿ� PLAYER�� ���� ��� */
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY()) < 200)
	{
		if (enemy->transform->GetX() < enemy->GetPlayerTransform()->GetX())
			enemy->enemyinfo->SetDir(false);
		else
			enemy->enemyinfo->SetDir(true);
		return new LukeRunState();
	}

	return nullptr;
}

void LukeWalkState::Enter(EnemyAI* enemy)
{
	_moveStartTime = 0.0f;
	_moveMaxTime = 5.0f;

	/* PATROL ANGLE */
	_angle = GetAngle(enemy->transform->GetX(), enemy->transform->GetY(), enemy->patrolPoint.first, enemy->patrolPoint.second);
	
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("luke_walk_right", true);
	else
		enemy->ChangeClip("luke_walk_left", true);
}

void LukeWalkState::Exit(EnemyAI* enemy)
{
}