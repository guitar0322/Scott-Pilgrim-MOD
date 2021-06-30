#include "stdafx.h"
#include "PlayerGroundState.h"
#include "PlayerIdleState.h"
#include "Player.h"

PlayerState * PlayerGroundState::InputHandle(Player * player)
{
	if (KEYMANAGER->isOnceKeyUp('A'));
	if (KEYMANAGER->isOnceKeyUp('D'));
	if (KEYMANAGER->isOnceKeyUp('W'));
	if (KEYMANAGER->isOnceKeyUp('S'));

	if (player->groundZCheck == true && _jumpTime >= 0.4f)
	{
		player->jumpZ = false;
		player->groundZCheck = false;


		return new PlayerIdleState();
	}

	if (player->groundCheck == true && _jumpTime >= 0.7f) 
	{
		player->jumpZ = false;
		player->groundCheck = false;


		return new PlayerIdleState();
	}

	return nullptr;
}

void PlayerGroundState::Update(Player * player)
{
	_jumpTime += TIMEMANAGER->getElapsedTime();
}

void PlayerGroundState::Enter(Player * player)
{
	_jumpTime = 0;
	player->isRun = false;
	player->runKeyPress = false;

	if (player->isCatch == true)
	{
		if (player->dir == false)
		{
			player->ChangeClip("two_hand_ground_right", true);
		}
		else
		{
			player->ChangeClip("two_hand_ground_left", true);
		}
	}
	else
	{
		if (player->dir == false)
		{
			player->ChangeClip("ground_right", true);
		}
		else
		{
			player->ChangeClip("ground_left", true);
		}
	}
	

}

void PlayerGroundState::Exit(Player * player)
{
}
