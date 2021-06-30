#include "stdafx.h"
#include "PlayerBreakState.h"
#include "PlayerWalkState.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
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


	if (player->dir == false)
	{
		EFFECTMANAGER->EmissionEffect("run_or_break_effect_right", player->transform->GetX()+8, player->zOrder->GetZ() - 12);
	}
	else
	{
		EFFECTMANAGER->EmissionEffect("run_or_break_effect_left", player->transform->GetX()- 8, player->zOrder->GetZ() - 12);
	}
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
