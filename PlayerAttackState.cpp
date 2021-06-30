#include "stdafx.h"
#include "PlayerAttackState.h"
#include "PlayerIdleState.h"
#include "PlayerDoubleAttackState.h"
#include "Player.h"

PlayerState * PlayerAttackState::InputHandle(Player * player)
{
	//Ÿ�ӸŴ����� ������ �������Ǹ� idle ������Ʈ�� ����

	_attackTime += TIMEMANAGER->getElapsedTime();

	if (_attackTime > 0.5f && _doubleAttack != true && player->pressL == false)
	{
		player->isUppercut = false;
		return new PlayerIdleState();
	}
	
	if (KEYMANAGER->isOnceKeyDown('L') && _doubleAttack == true) //��Ÿ�� ��� ���� ��
	{
		player->pressL = true;
		return new PlayerDoubleAttackState();
	}
	

	return nullptr;
}

void PlayerAttackState::Update(Player * player)
{
	//int enemyHp = player->enemyInfo->GetHp();

	if (KEYMANAGER->isStayKeyDown('L'))
	{
		if (player->pressL == false && _doubleAttack == false)
		{
			_attackTime = 0;
			player->pressL = true;
		}

	}

	//�ִ� �������̵Ǹ� attack2�̹����� 
	if (player->animator->GetEnd())
	{
		if (player->pressL == true)
		{
			_doubleAttack = true;
			player->pressL = false;
			player->isUppercut = false;			//���ʹ̰� ���� �� 3��Ÿ Ȯ�� ���Ͽ�

			if (player->dir == false)
			{
				player->ChangeClip("attack2_right", true);
			}
			else
			{
				player->ChangeClip("attack2_left", true);
			}


			if (GetDistance(player->transform->GetX(), player->transform->GetY(),
				player->GetEnemyTransform()->GetX(), player->GetEnemyTransform()->GetY()) < 50)
			{
				player->enemy->GetComponent<EnemyInfo>()->Hit(player->attack);
				EFFECTMANAGER->EmissionEffect("attack_effect", player->GetEnemyTransform()->GetX(), player->GetEnemyTransform()->GetY());
				player->isUppercut = true; //���ʹ̰� ���� �� 3��Ÿ ����Ŀ��
			}
		}
	}
	
}

void PlayerAttackState::Enter(Player * player)
{
	if (GetDistance(player->transform->GetX(), player->transform->GetY(),
		player->GetEnemyTransform()->GetX(), player->GetEnemyTransform()->GetY()) < 50)
	{
		player->enemy->GetComponent<EnemyInfo>()->Hit(player->attack);
		EFFECTMANAGER->EmissionEffect("attack_effect", player->GetEnemyTransform()->GetX(), player->GetEnemyTransform()->GetY());
		
	}
	if (player->dir == false)
	{
		player->ChangeClip("attack1_right", true);
	}
	else
	{
		player->ChangeClip("attack1_left", true);
	}
}
	

void PlayerAttackState::Exit(Player * player)
{

}
