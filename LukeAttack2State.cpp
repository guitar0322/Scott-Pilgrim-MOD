#include "stdafx.h"
#include "LukeAttack2State.h"
#include "LukeAttack3State.h"

EnemyState* LukeAttack2State::Update(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == true)
		enemy->enemyinfo->SetDir(false);
	else
		enemy->enemyinfo->SetDir(true);

	/* ��ġ ��ǥ ���� */
	if (enemy->animator->GetEnd())
	{
		if (enemy->enemyinfo->GetDir())
		{
			enemy->transform->MoveX(40);
		}
		else
		{
			enemy->transform->MoveX(-40);
		}
		return new LukeAttack3State();
	}
    return nullptr;
}

void LukeAttack2State::Enter(EnemyAI* enemy)
{
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->transform->GetY()) > 20)
	{
		enemy->GetPlayer()->GetComponent<Player>()->Hit(enemy->enemyinfo->GetDamage());
	}

	/* ��ġ ��ǥ ���� */
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->transform->MoveX(40);
		enemy->ChangeClip("luke_attack2_right", true);
	}
	else
	{
		enemy->transform->MoveX(-40);
		enemy->ChangeClip("luke_attack2_left", true);
	}
}

void LukeAttack2State::Exit(EnemyAI* enemy)
{
}
