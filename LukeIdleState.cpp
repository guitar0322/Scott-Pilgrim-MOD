#include "stdafx.h"
#include "LukeIdleState.h"
#include "LukeRunState.h"

EnemyState* LukeIdleState::Update(EnemyAI* enemy)
{
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
	_idelTime = 0;
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("luke_idle_right", true);
	else
		enemy->ChangeClip("luke_idle_left", true);
}

void LukeIdleState::Exit(EnemyAI* enemy)
{
}