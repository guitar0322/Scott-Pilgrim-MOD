#include "stdafx.h"
#include "PlayerBreakState.h"
#include "PlayerWalkState.h"
#include "PlayerIdleState.h"
#include "player.h"

PlayerState* PlayerBreakState::InputHandle(Player* player)
{
	if (_dashSpeed < 0)
	{
		return new PlayerIdleState();
	}

	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player->dir = false;
		player->runKeyPress = true;
		return new PlayerWalkState();
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		player->dir = true;
		player->runKeyPress = true;
		return new PlayerWalkState();
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		player->runKeyPress = false;
		player->jumpZ = true;
		player->dirZ = true;
		return new PlayerWalkState();
	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		player->runKeyPress = false;
		player->jumpZ = true;
		player->dirZ = false;
		return new PlayerWalkState();
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
}

void PlayerBreakState::Enter(Player * player)
{
	_dashSpeed = 100;
	player->isRun = false;
	if (player->isCatch == true)
	{
		if (player->dir == false)

			player->ChangeClip("two_hand_idle_right", false);
		else
			player->ChangeClip("two_hand_idle_left", false);
	}
	else
	{
		if (player->dir == false)
		{
			player->ChangeClip("idle_right", false);
		}
		else
		{
			player->ChangeClip("idle_left", false);
		}
	}
}

void PlayerBreakState::Exit(Player * player)
{

}
