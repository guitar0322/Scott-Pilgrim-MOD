#include "stdafx.h"
#include "PlayerBreakState.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "player.h"

PlayerState * PlayerBreakState::InputHandle(Player * player)
{
	if (_dashSpeed < 0)
	{
		return new PlayerIdleState();
	}

	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (player->isCatch == true)
		{
			player->dir = false;
			player->ChangeClip("two_hand_walk_right", true);
			return new PlayerWalkState();
		}
		else
		{
			player->dir = false;
			player->ChangeClip("walk_right", true);
			return new PlayerWalkState();
		}

	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		if (player->dir == true)
			player->runKeyPress = false;
		return new PlayerIdleState();
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{

		if (player->isCatch == true)
		{
			player->dir = true;
			player->ChangeClip("two_hand_walk_left", true);
			return new PlayerWalkState();
		}
		else
		{
			player->dir = true;
			player->ChangeClip("walk_left", true);
			return new PlayerWalkState();
		}
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		if (player->dir == false)
			player->runKeyPress = false;
		return new PlayerIdleState();
	}
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		player->runKeyPress = false;

		return new PlayerIdleState();
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		player->runKeyPress = false;

		return new PlayerIdleState();
	}

	return nullptr;
}

void PlayerBreakState::Update(Player * player)
{
	_dashSpeed -= player->GetFriction() * TIMEMANAGER->getElapsedTime();
	if (player->dir == false)
	{
		player->transform->MoveX(_dashSpeed * TIMEMANAGER->getElapsedTime());
	}
	else
	{
		player->transform->MoveX(-_dashSpeed * TIMEMANAGER->getElapsedTime());
	}

	if (KEYMANAGER->isStayKeyDown('D') && player->dir == false)
	{
		player->transform->MoveX(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('A') && player->dir == true)
	{
		player->transform->MoveX(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->runKeyPress = false;
		player->zOrder->MoveZ(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->runKeyPress = false;
		player->zOrder->MoveZ(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}


}

void PlayerBreakState::Enter(Player * player)
{
	_dashSpeed = 100;

	if (player->isCatch == true)
	{
		if (player->dir == false)

			player->ChangeClip("two_hand_idle_right", true);
		else
			player->ChangeClip("two_hand_idle_left", true);
	}
	else
	{
		if (player->dir == false)
		{
			player->ChangeClip("idle_right", true);
		}
		else
		{
			player->ChangeClip("idle_left", true);
		}
	}
}

void PlayerBreakState::Exit(Player * player)
{



}
