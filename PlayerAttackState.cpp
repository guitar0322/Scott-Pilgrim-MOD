#include "stdafx.h"
#include "PlayerAttackState.h"
#include "PlayerIdleState.h"
#include "PlayerDoubleAttackState.h"
#include "Player.h"

PlayerState * PlayerAttackState::InputHandle(Player * player)
{
	//타임매니저로 공격이 마무리되면 idle 스테이트로 변경

	_attackTime += TIMEMANAGER->getElapsedTime();

	if (_attackTime > 0.5f && _doubleAttack != true && player->pressL == false)
	{
		player->isUppercut = false;
		return new PlayerIdleState();
	}
	
	if (KEYMANAGER->isOnceKeyDown('L') && _doubleAttack == true) //연타에 들어 갔을 때
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

	//최대 프레임이되면 attack2이미지로 
	if (player->animator->GetEnd())
	{
		if (player->pressL == true)
		{
			_doubleAttack = true;
			player->pressL = false;
			player->isUppercut = false;			//에너미가 없을 때 3연타 확인 위하여

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
				player->isUppercut = true; //에너미가 있을 때 3연타 어퍼커로
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
