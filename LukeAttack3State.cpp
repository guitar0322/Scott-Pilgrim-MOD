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
		/* ��ġ ��ǥ ���� */
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
	enemy->Attack(70);

	/* ��ġ ��ǥ ���� */
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
