#include "stdafx.h"
#include "LukeIdleState.h"
#include "LukeWalkState.h"
#include "LukeRunState.h"

EnemyState* LukeIdleState::Update(EnemyAI* enemy)
{
	if (enemy->transform->GetX() < enemy->GetPlayerTransform()->GetX())
	{
		enemy->enemyinfo->SetDir(false);
	}
	else
	{
		enemy->enemyinfo->SetDir(true);
	}

	/* 210630 Patrol ���� */
	_idleTime += TIMEMANAGER->getElapsedTime();
	if (_idleTime >= _idleMaxTime)
	{
		_isPatrol = true;
		_idleTime = 0;
		int patrolIdx = RND->getInt(4);
		enemy->deltaX = RND->getFromFloatTo(30.f, 60.f);
		enemy->deltaY = RND->getFromFloatTo(30.f, 60.f);

		switch (patrolIdx)
		{
		// ��1��и�
		case 0:
			enemy->patrolPoint = { enemy->transform->GetX() + enemy->deltaX, enemy->transform->GetY() - enemy->deltaY };
			break;

		// ��2��и�
		case 1:
			enemy->patrolPoint = { enemy->transform->GetX() + enemy->deltaX, enemy->transform->GetY() + enemy->deltaY };
			break;

		// ��3��и�
		case 2:
			enemy->patrolPoint = { enemy->transform->GetX() - enemy->deltaX, enemy->transform->GetY() + enemy->deltaY };
			break;

		// ��4��и�
		case 3:
			enemy->patrolPoint = { enemy->transform->GetX() - enemy->deltaX, enemy->transform->GetY() - enemy->deltaY };
			break;
		}
		return new LukeWalkState();
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

void LukeIdleState::Enter(EnemyAI* enemy)
{
	_isPatrol = false;
	_idleTime = 0.0f;
	_idleMaxTime = 5.0f;

	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->ChangeClip("luke_idle_right", true);
	}
	else
	{
		enemy->ChangeClip("luke_idle_left", true);
	}
}

void LukeIdleState::Exit(EnemyAI* enemy)
{

}