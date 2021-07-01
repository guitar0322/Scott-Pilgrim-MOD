#include "stdafx.h"
#include "JesseIdleState.h"
#include "JesseAttackState.h"

EnemyState* JesseAttackState::Update(EnemyAI* enemy)
{
	/* EDIT �ʿ� - 3��Ÿ ���� ��� ���� �� IDEL�� IF�� �Ἥ �ϱ� */
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
		return new JesseAttackState();
		// return new JesseIdleState();
	}

    return nullptr;
}

void JesseAttackState::Enter(EnemyAI* enemy)
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
		enemy->ChangeClip("jesse_attack_right", true);
	}
	else
	{
		enemy->transform->MoveX(-40);
		enemy->ChangeClip("jesse_attack_left", true);
	}
}

void JesseAttackState::Exit(EnemyAI* enemy)
{
}
