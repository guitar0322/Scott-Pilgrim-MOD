#include "stdafx.h"
#include "PlayerAttackState.h"
#include "PlayerIdleState.h"
#include "Player.h"

PlayerState * PlayerAttackState::InputHandle(Player * player)
{
	_count++;

	if (_count > 100 && player->dir == false)
	{

		return new PlayerIdleState();


		_count = 0;
	}
	if (_count > 150 && player->dir == true)
	{
		return new PlayerIdleState();


		_count = 0;
	}


	return nullptr;
}

void PlayerAttackState::Update(Player * player)
{
	
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		if (player->dir == false)
		{
			player->ChangeClip("attack2_right", false);
		}
		else
		{
			player->ChangeClip("attack2_left", false);

		}

	}



}

void PlayerAttackState::Enter(Player * player)
{


	if (player->dir == false)
	{
		player->ChangeClip("attack1_right", false);
	}
	else
	{
		player->ChangeClip("attack1_left", false);
	}
}

void PlayerAttackState::Exit(Player * player)
{

}
