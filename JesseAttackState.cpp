#include "stdafx.h"
#include "JesseIdleState.h"
#include "JesseAttackState.h"

EnemyState* JesseAttackState::Update(EnemyAI* enemy)
{
	/* EDIT 필요 - 3연타 동일 모션 공격 후 IDEL로 IF문 써서 하기 */
	if (enemy->enemyinfo->GetDir() == true)
		enemy->enemyinfo->SetDir(false);
	else
		enemy->enemyinfo->SetDir(true);

	/* 위치 좌표 보정 */
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

	/* 위치 좌표 보정 */
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
