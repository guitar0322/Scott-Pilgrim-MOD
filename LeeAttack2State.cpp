#include "stdafx.h"
#include "LeeAttack2State.h"
#include "LeeAttack3State.h"

EnemyState* LeeAttack2State::Update(EnemyAI* enemy)
{
    if (enemy->enemyinfo->GetDir() == true)
		enemy->enemyinfo->SetDir(false);
	else
		enemy->enemyinfo->SetDir(true);

	/* 위치 좌표 보정 */
	if (enemy->animator->GetEnd())
	{
		if (enemy->enemyinfo->GetDir())
		{
			enemy->transform->MoveX(20);
		}
		else
		{
			enemy->transform->MoveX(-20);
		}
		return new LeeAttack3State();
	}
	return nullptr;
}

void LeeAttack2State::Enter(EnemyAI* enemy)
{
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->transform->GetY()) > 20)
	{
		enemy->GetPlayer()->GetComponent<Player>()->Hit(enemy->enemyinfo->GetDamage());
	}

	/* 위치 좌표 보정 */
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->transform->MoveX(20);
		enemy->ChangeClip("lee_attack2_right", true);
	}
	else
	{
		enemy->transform->MoveX(-20);
		enemy->ChangeClip("lee_attack2_left", true);
	}
}

void LeeAttack2State::Exit(EnemyAI* enemy)
{
}
