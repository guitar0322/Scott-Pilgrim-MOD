#include "stdafx.h"
#include "Enemy.h"
#include "LeeIdleState.h"
#include "LeeWalkState.h"
#include "LeeRunState.h"
#include "LeeAttack1State.h"
#include "LeeKickState.h"

EnemyState* LeeRunState::Update(EnemyAI* enemy)
{
	if (enemy->transform->GetX() < enemy->GetPlayerTransform()->GetX())
	{
		if (enemy->enemyinfo->GetDir() == true)
		{
			enemy->ChangeClip("lee_run_right", false);
			enemy->enemyinfo->SetDir(false);
		}
	}
	else
	{
		if (enemy->enemyinfo->GetDir() == false)
		{
			enemy->ChangeClip("lee_run_left", false);
			enemy->enemyinfo->SetDir(true);
		}
	}

	/* RUN ���� �� PLAYER�� ������ ��� ��� */
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY()) > 200)
	{
		return new LeeWalkState();
	}

	/* RUN ���� �� PLAYER ���� �� ������, Z�൵ ������ ���� ������� ��� */
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY()) < 100 &&
		enemy->zOrder->GetZ() - 6 <= enemy->GetPlayerTransform()->gameObject->GetComponent<ZOrder>()->GetZ() &&
		enemy->zOrder->GetZ() + 6 >= enemy->GetPlayerTransform()->gameObject->GetComponent<ZOrder>()->GetZ())
	{
		/* �޺����� OR ������ ���� �� �������� */
		int randomAttack = 0; // RND->getInt(2);
		switch (randomAttack)
		{
		case 0:
			return new LeeAttack1State();
		case 1:
			return new LeeKickState();
		}
	}

	float angle = GetAngle(enemy->transform->GetX(), enemy->zOrder->GetZ(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayer()->GetComponent<ZOrder>()->GetZ());

	enemy->transform->MoveX(_speed * TIMEMANAGER->getElapsedTime() * cosf(angle));
	enemy->zOrder->MoveZ(_speed * TIMEMANAGER->getElapsedTime() * -sinf(angle));

	return nullptr;
}

void LeeRunState::Enter(EnemyAI* enemy)
{
	/* �ȴ� �ӵ��� �ٴ� �ӵ��� �ٸ��Ƿ�, �ӵ� * 1.5 ���� */
	_speed = enemy->enemyinfo->GetSpeed() * 1.5;

	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("lee_run_right", true);
	else
		enemy->ChangeClip("lee_run_left", true);
}

void LeeRunState::Exit(EnemyAI* enemy)
{
}
