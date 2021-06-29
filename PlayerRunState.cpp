#include "stdafx.h"
#include "PlayerRunState.h"
#include "PlayerBreakState.h"
#include "PlayerJumpState.h"
#include "PlayerKickAttackState.h"
#include "PlayerAttackState.h"
#include "PlayerTwoHandAttackState.h"
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

	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		return new PlayerJumpState();
	}

	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		if (player->isCatch == false)
		{
			return new PlayerAttackState();
		}
		else
		{
			return new PlayerTwoHandAttackState();
;		}
	}
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		return new PlayerKickAttackState();

	}


	return nullptr;
}

void PlayerRunState::Update(Player * player)
{
	if (player->dir == false)
	{
		player->transform->MoveX(player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime());
	}
	else
	{
		player->transform->MoveX(-player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime());
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->zOrder->MoveZ(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->zOrder->MoveZ(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}

	
	

}

void PlayerRunState::Enter(Player * player)
{
	if (player->isCatch == true)
	{
		if (player->dir == false)
		{
			player->ChangeClip("two_hand_run_right", false);
		}
		else
		{
			player->ChangeClip("two_hand_run_left", false);
		}
	}
	else
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
	
}

void PlayerRunState::Exit(Player * player)
{
}
