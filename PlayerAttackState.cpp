#include "stdafx.h"
#include "PlayerAttackState.h"
#include "PlayerIdleState.h"
#include "PlayerDoubleAttackState.h"
#include "Player.h"

PlayerState * PlayerAttackState::InputHandle(Player * player)
{
	//타임매니저로 공격이 마무리되면 idle 스테이트로 변경

	_attackTime += TIMEMANAGER->getElapsedTime();

	if (_attackTime > 0.5f &&  _doubleAttack == false && player->pressL == false)
	{
		player->isUppercut = false;
		return new PlayerIdleState();
	}
	//1연타 공격 시 L키 안 누르고 이미지 프레임이 끝나면 기본자세

	if (_attackTime > 0.5f && _doubleAttack == true && player->pressL == false)
	{
		player->isUppercut = false;
		_doubleAttack = false;
		player->pressL == false;
		_attackTime = 0;

		return new PlayerIdleState();
	}
	//L키 누르고 0.7초이상 지나면 기본자세

	if (_attackTime < 0.5f && _doubleAttack == true && player->pressL == true) //연타에 들어 갔을 때
	{
		_attackTime = 0;

		return new PlayerDoubleAttackState();
		
	}
	
	//0.7초 안에 L키가 눌려지고 연타공격에 들어가고 한번 더 L키가 눌렸을 시 3연타 공격을 넘어간다

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

		//최대 프레임이되면 attack2이미지로 
		if (player->animator->GetEnd())
		{
			if (player->pressL == true)
			{
				_doubleAttack = true;
				player->pressL = false;

				player->isUppercut = false;		//에너미가 없을 때 3연타 확인 위하여

				if (GetDistance(player->transform->GetX(), player->transform->GetY(),
					player->GetEnemyTransform()->GetX(), player->GetEnemyTransform()->GetY()) < 50)
				{
					player->enemy->GetComponent<EnemyInfo>()->Hit(player->attack);
					EFFECTMANAGER->EmissionEffect("attack_effect", player->GetEnemyTransform()->GetX(), player->GetEnemyTransform()->GetY());
					player->isUppercut = true;
					player->pressL = true;
				}

				//거리내에 에너미가 있을 때 3타 공격은 어퍼컷으로 한다.

				if (player->dir == false)
				{
					player->ChangeClip("attack2_right", true);
				}
				else
				{
					player->ChangeClip("attack2_left", true);
				}

				// 그리고 1연타 공격이 마무리되고 L키를 누를 시 2연타 공격으로 넘어간다.
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
	//1연타 공격 시 에너미와 플레이어가 거리 내에 있으면 공격에 들어간다.

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
