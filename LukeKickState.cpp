#include "stdafx.h"
#include "LukeIdleState.h"
#include "LukeKickState.h"

EnemyState* LukeKickState::Update(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == true)
	{
		enemy->enemyinfo->SetDir(false);
	}
	else
	{
		enemy->enemyinfo->SetDir(true);
	}

	/* 위치 좌표 보정 */
	if (enemy->animator->GetEnd())
	{
		if (enemy->enemyinfo->GetDir())
		{
			enemy->transform->MoveX(25);
		}
		else
		{
			enemy->transform->MoveX(-25);
		}
		return new LukeIdleState();
	}

	return nullptr;
}

void LukeKickState::Enter(EnemyAI* enemy)
{
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->transform->GetY()) > 20)
	{
		enemy->GetPlayer()->GetComponent<Player>()->Hit(enemy->enemyinfo->GetDamage());
	}

	/* 위치 좌표 보정 */
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->transform->MoveX(25);
		enemy->ChangeClip("luke_kick_right", true);
	}
	else
	{
		enemy->transform->MoveX(-25);
		enemy->ChangeClip("luke_kick_left", true);
	}
}

void LukeKickState::Exit(EnemyAI* enemy)
{
}
