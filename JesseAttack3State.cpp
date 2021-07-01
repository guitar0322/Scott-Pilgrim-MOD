#include "stdafx.h"
#include "JesseAttack3State.h"
#include "JesseIdleState.h"

EnemyState* JesseAttack3State::Update(EnemyAI* enemy)
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
		return new JesseIdleState();
	}
	return nullptr;
}

void JesseAttack3State::Enter(EnemyAI* enemy)
{
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->transform->GetY()) > 2)
	{
		enemy->GetPlayer()->GetComponent<Player>()->Hit(enemy->enemyinfo->GetDamage());
	}

	/* ��ġ ��ǥ ���� */
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->transform->MoveX(40);
		enemy->ChangeClip("jesse_attack_right", true);
	}
	else
	{
		enemy->transform->MoveX(-40);
		enemy->ChangeClip("jesse_attack_left", true);
	}
}

void JesseAttack3State::Exit(EnemyAI* enemy)
{
}
