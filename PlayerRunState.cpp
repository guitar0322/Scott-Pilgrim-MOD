#include "stdafx.h"
#include "PlayerRunState.h"
#include "PlayerBreakState.h"
#include "PlayerJumpState.h"
#include "PlayerKickAttackState.h"
#include "PlayerAttackState.h"
#include "Player.h"

PlayerState * PlayerRunState::InputHandle(Player * player)
{
	if (KEYMANAGER->isOnceKeyUp('D'))
	{

		return new PlayerBreakState();
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{

		return new PlayerBreakState();

	}

	if (KEYMANAGER->isStayKeyDown('J'))
	{
		if (player->dir == false)
		{
			return new PlayerJumpState();

		}
		else
		{
			return new PlayerJumpState();
		}

	}

	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		if (player->dir == false)
		{
			player->attackChange = true; //2번공격
			return new PlayerAttackState();

		}
		else
		{
			player->attackChange = true; //2번공격
			return new PlayerAttackState();
		}
	}
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		if (player->dir == false)
		{
			return new PlayerKickAttackState();

		}
		else
		{
			return new PlayerKickAttackState();
		}
	}


	return nullptr;
}

void PlayerRunState::Update(Player * player)
{
	if (player->dir == false)
	{
		player->transform->MoveX(player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime());
		player->ground->MoveX(player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime());
	}
	else
	{
		player->transform->MoveX(-player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime());
		player->ground->MoveX(-player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime());
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->ground->MoveY(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
		player->zOrder->MoveZ(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->ground->MoveY(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
		player->zOrder->MoveZ(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}

	
	

}

void PlayerRunState::Enter(Player * player)
{
	if (player->dir == false)
	{
		player->ChangeClip("run_right", false);
	}
	else
	{
		player->ChangeClip("run_left", false);
	}
}

void PlayerRunState::Exit(Player * player)
{
}
