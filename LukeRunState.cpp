#include "stdafx.h"
#include "Enemy.h"
#include "LukeIdleState.h"
#include "LukeRunState.h"

EnemyState* LukeRunState::Update(Enemy* enemy)
{
	if (enemy->transform->GetX() < enemy->GetPlayerTransform()->GetX())
	{
		if (enemy->GetDir() == true)
		{
			enemy->ChangeClip("rnu_right", false);
			enemy->SetDir(false);
		}
	}
	else
	{
		if (enemy->GetDir() == false)
		{
			enemy->ChangeClip("rnu_left", false);
			enemy->SetDir(true);
		}
	}

	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY()) > 200)
	{
		return new LukeIdleState();
	}

	// TODO - AI XÃà, YÃà, 
	float angle = GetAngle(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY());

	enemy->transform->Move(enemy->GetSpeed() * TIMEMANAGER->getElapsedTime() * cosf(angle),
		enemy->GetSpeed() * TIMEMANAGER->getElapsedTime() * -sinf(angle));

	return nullptr;
}

void LukeRunState::Enter(Enemy* enemy)
{
	if (enemy->GetDir() == false)
		enemy->ChangeClip("luke_runRight", true);
	else
		enemy->ChangeClip("luke_runLeft", true);
}

void LukeRunState::Exit(Enemy* enemy)
{
}
