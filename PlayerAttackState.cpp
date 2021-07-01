#include "stdafx.h"
#include "PlayerAttackState.h"
#include "PlayerIdleState.h"
#include "PlayerDoubleAttackState.h"
#include "Player.h"

PlayerState * PlayerAttackState::InputHandle(Player * player)
{
	//Ÿ�ӸŴ����� ������ �������Ǹ� idle ������Ʈ�� ����

	_attackTime += TIMEMANAGER->getElapsedTime();

	if (_attackTime > 0.5f &&  _doubleAttack == false && player->pressL == false)
	{
		player->isUppercut = false;
		return new PlayerIdleState();
	}
	//1��Ÿ ���� �� LŰ �� ������ �̹��� �������� ������ �⺻�ڼ�

	if (_attackTime > 0.5f && _doubleAttack == true && player->pressL == false)
	{
		player->isUppercut = false;
		_doubleAttack = false;
		player->pressL == false;
		_attackTime = 0;

		return new PlayerIdleState();
	}
	//LŰ ������ 0.7���̻� ������ �⺻�ڼ�

	if (_attackTime < 0.5f && _doubleAttack == true && player->pressL == true) //��Ÿ�� ��� ���� ��
	{
		_attackTime = 0;

		return new PlayerDoubleAttackState();
		
	}
	
	//0.7�� �ȿ� LŰ�� �������� ��Ÿ���ݿ� ���� �ѹ� �� LŰ�� ������ �� 3��Ÿ ������ �Ѿ��

	return nullptr;
}

void PlayerAttackState::Update(Player * player)
{

	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		if (player->pressL == false && _doubleAttack == false)
		{
			_attackTime = 0;
			player->pressL = true;
		}

		//�ִ� �������̵Ǹ� attack2�̹����� 
		if (player->animator->GetEnd())
		{
			if (player->pressL == true)
			{
				_doubleAttack = true;
				player->pressL = false;

				player->isUppercut = false;		//���ʹ̰� ���� �� 3��Ÿ Ȯ�� ���Ͽ�

				if (GetDistance(player->transform->GetX(), player->transform->GetY(),
					player->GetEnemyTransform()->GetX(), player->GetEnemyTransform()->GetY()) < 50)
				{
					player->enemy->GetComponent<EnemyInfo>()->Hit(player->attack);
					EFFECTMANAGER->EmissionEffect("attack_effect", player->GetEnemyTransform()->GetX(), player->GetEnemyTransform()->GetY());
					player->isUppercut = true;
					player->pressL = true;
				}

				//�Ÿ����� ���ʹ̰� ���� �� 3Ÿ ������ ���������� �Ѵ�.

				if (player->dir == false)
				{
					player->ChangeClip("attack2_right", true);
				}
				else
				{
					player->ChangeClip("attack2_left", true);
				}

				// �׸��� 1��Ÿ ������ �������ǰ� LŰ�� ���� �� 2��Ÿ �������� �Ѿ��.
			}
		}
	}
	
	
}

void PlayerAttackState::Enter(Player * player)
{
	player->pressL = false;
	_doubleAttack = false;
	_attackTime = 0;

	if (GetDistance(player->transform->GetX(), player->transform->GetY(),
		player->GetEnemyTransform()->GetX(), player->GetEnemyTransform()->GetY()) < 50)
	{
		player->enemy->GetComponent<EnemyInfo>()->Hit(player->attack);
		EFFECTMANAGER->EmissionEffect("attack_effect", player->GetEnemyTransform()->GetX(), player->GetEnemyTransform()->GetY());
		
	}
	//1��Ÿ ���� �� ���ʹ̿� �÷��̾ �Ÿ� ���� ������ ���ݿ� ����.

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
