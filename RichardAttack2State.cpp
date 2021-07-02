#include "stdafx.h"
#include "RichardAttack2State.h"
#include "RichardAttack3State.h"

EnemyState* RichardAttack2State::Update(EnemyAI* enemy)
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
		return new RichardAttack3State();
	}
	return nullptr;
}

void RichardAttack2State::Enter(EnemyAI* enemy)
{
	enemy->Attack(70);

	/* ��ġ ��ǥ ���� */
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->transform->MoveX(40);
		enemy->ChangeClip("mike_attack2_right", true);
	}
	else
	{
		enemy->transform->MoveX(-40);
		enemy->ChangeClip("mike_attack2_left", true);
	}
}

void RichardAttack2State::Exit(EnemyAI* enemy)
{
}
