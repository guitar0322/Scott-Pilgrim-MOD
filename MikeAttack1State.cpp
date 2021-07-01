#include "stdafx.h"
#include "MikeAttack1State.h"
#include "MikeAttack2State.h"

EnemyState* MikeAttack1State::Update(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == true)
		enemy->enemyinfo->SetDir(false);
	else
		enemy->enemyinfo->SetDir(true);

	/* ��ġ ��ǥ ���� */
	if (enemy->animator->GetEnd())
	{
		enemy->transform->MoveY(-10);
		if (enemy->enemyinfo->GetDir())
		{
			enemy->transform->MoveX(40);
		}
		else
		{
			enemy->transform->MoveX(-40);
		}
		return new MikeAttack2State();
	}

	return nullptr;
}

void MikeAttack1State::Enter(EnemyAI* enemy)
{
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->transform->GetY()) > 20)
	{
		enemy->GetPlayer()->GetComponent<Player>()->Hit(enemy->enemyinfo->GetDamage());
	}

	/* ��ġ ��ǥ ���� */
	enemy->transform->MoveY(10);
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->transform->MoveX(40);
		enemy->ChangeClip("mike_attack1_right", true);
	}
	else
	{
		enemy->transform->MoveX(-40);
		enemy->ChangeClip("mike_attack1_left", true);
	}
}

void MikeAttack1State::Exit(EnemyAI* enemy)
{
}
