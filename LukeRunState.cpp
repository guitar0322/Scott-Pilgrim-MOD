#include "stdafx.h"
#include "Enemy.h"
#include "LukeIdleState.h"
#include "LukeRunState.h"
#include "LukeAttack1State.h"

EnemyState* LukeRunState::Update(EnemyAI* enemy)
{
	if (enemy->transform->GetX() < enemy->GetPlayerTransform()->GetX())
	{
		if (enemy->enemyinfo->GetDir() == true)
		{
			enemy->ChangeClip("luke_run_right", false);
			enemy->enemyinfo->SetDir(false);
		}
	}
	else
	{
		if (enemy->enemyinfo->GetDir() == false)
		{
			enemy->ChangeClip("luke_run_left", false);
			enemy->enemyinfo->SetDir(true);
		}
	}

	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY()) > 200)
	{
		return new LukeIdleState();
	}
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY()) < 100)
	{
		return new LukeAttack1State();
	}

	// TODO - AI XÃà, YÃà, 
	float angle = GetAngle(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY());

	enemy->transform->Move(enemy->enemyinfo->GetSpeed() * TIMEMANAGER->getElapsedTime() * cosf(angle),
		enemy->enemyinfo->GetSpeed() * TIMEMANAGER->getElapsedTime() * -sinf(angle));

	return nullptr;
}

void LukeRunState::Enter(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("luke_run_right", true);
	else
		enemy->ChangeClip("luke_run_left", true);
}

void LukeRunState::Exit(EnemyAI* enemy)
{
}