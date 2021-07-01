#include "stdafx.h"
#include "LukeAttack3State.h"
#include "LukeIdleState.h"

EnemyState* LukeAttack3State::Update(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == true)
		enemy->enemyinfo->SetDir(false);	
	else
		enemy->enemyinfo->SetDir(true);

	if (enemy->animator->GetEnd())
	{
		/* 위치 좌표 보정 */
		enemy->transform->MoveY(20);
		if (enemy->enemyinfo->GetDir())
		{
			enemy->transform->MoveX(40);
		}
		else
		{
			enemy->transform->MoveX(-40);
		}
		return new LukeIdleState();
	}
    return nullptr;
}

void LukeAttack3State::Enter(EnemyAI* enemy)
{
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->transform->GetY()) > 20)
	{
		enemy->GetPlayer()->GetComponent<Player>()->Hit(enemy->enemyinfo->GetDamage());
	}

	/* 위치 좌표 보정 */
	enemy->transform->MoveY(-20);
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->transform->MoveX(40);
		enemy->ChangeClip("luke_attack3_right", true);
	}
	else
	{
		enemy->transform->MoveX(-40);
		enemy->ChangeClip("luke_attack3_left", true);
	}
}

void LukeAttack3State::Exit(EnemyAI* enemy)
{
}
