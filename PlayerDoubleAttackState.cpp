#include "stdafx.h"
#include "PlayerDoubleAttackState.h"
#include "PlayerIdleState.h"
#include "Player.h"

PlayerState * PlayerDoubleAttackState::InputHandle(Player * player)
{
	if (player->animator->GetEnd())
	{
		player->isUppercut = false;
		player->pressL = false;
		return new PlayerIdleState();
	}

	return nullptr;
}

void PlayerDoubleAttackState::Update(Player * player)
{


}

void PlayerDoubleAttackState::Enter(Player * player)
{
	_speedY = 50;

	if (player->isUppercut == true)
	{
		if (player->dir == false)
		{
			player->ChangeClip("attack4_right", true);
		}
		else
		{
			player->ChangeClip("attack4_left", true);
		}
		player->enemy->GetComponent<EnemyInfo>()->Hit(player->attack);
		EFFECTMANAGER->EmissionEffect("attack_effect", player->GetEnemyTransform()->GetX(), player->GetEnemyTransform()->GetY());

	}
	else
	{
		if (player->dir == false)
		{
			player->ChangeClip("attack3_right", true);
		}
		else
		{
			player->ChangeClip("attack3_left", true);
		}
	
	}



}

void PlayerDoubleAttackState::Exit(Player * player)
{
}
