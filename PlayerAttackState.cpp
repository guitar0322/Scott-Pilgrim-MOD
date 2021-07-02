#include "stdafx.h"
#include "PlayerAttackState.h"
#include "PlayerIdleState.h"
#include "PlayerDoubleAttackState.h"
#include "Player.h"

PlayerState * PlayerAttackState::InputHandle(Player * player)
{
	//Ÿ�ӸŴ����� ������ �������Ǹ� idle ������Ʈ�� ����

	_attackTime += TIMEMANAGER->getElapsedTime();

	if (_attackTime > 0.5f)
	{
		if (_doubleAttack == false)
			return new PlayerIdleState();
		else
			return new PlayerDoubleAttackState();
	}

	return nullptr;
}

void PlayerAttackState::Update(Player * player)
{
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		if (player->pressL == false)
		{
			_attackTime = 0;
			player->pressL = true;
		}
		else {
			_doubleAttack = true;
		}
		//�ִ� �������̵Ǹ� attack2�̹����� 
		if (player->animator->GetEnd())
		{
			if (player->pressL == true && _doubleAttack == false)
			{
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
			Attack(player);
		}
	}
}

void PlayerAttackState::Enter(Player * player)
{
	Attack(player);
	player->pressL = false;
	_doubleAttack = false;
	_attackTime = 0;
	player->isUppercut = false;
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

void PlayerAttackState::Attack(Player* player)
{
	vector<GameObject*> _sectorEnemyV = ENEMYMANAGER->GetSectorEnemy();
	for (int i = 0; i < _sectorEnemyV.size(); i++)
	{
		if (_sectorEnemyV[i]->isActive == false) continue;
		float distance =
			GetDistance(player->transform->GetX(), player->transform->GetY(),
				_sectorEnemyV[i]->transform->GetX(), _sectorEnemyV[i]->transform->GetY());
		float distanceZ = player->zOrder->GetZ() - _sectorEnemyV[i]->GetComponent<ZOrder>()->GetZ();
		if (distanceZ < 0)
			distanceZ *= -1;
		if (distance < 100 && distanceZ < 10)
		{
			_sectorEnemyV[i]->GetComponent<EnemyAI>()->Hit(player->attack);

			if(player->pressL == true)
				player->isUppercut = true;

			if (player->dir == false)
			{
				EFFECTMANAGER->EmissionEffect("attack_effect", player->transform->GetX() + 60, player->transform->GetY() - 10);
			}
			else
			{
				EFFECTMANAGER->EmissionEffect("attack_effect", player->transform->GetX() - 60, player->transform->GetY() - 10);
			}
		}
	}
}
