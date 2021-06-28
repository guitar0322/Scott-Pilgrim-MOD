#include "stdafx.h"
#include "PlayerWalkState.h"
#include "PlayerIdleState.h"
#include "PlayerRunState.h"
#include "PlayerJumpState.h"
#include "PlayerKickAttackState.h"
#include "PlayerAttackState.h"
#include "PlayerFallState.h"
#include "PlayerTwoHandAttackState.h"
#include "Player.h"


PlayerState * PlayerWalkState::InputHandle(Player * player)
{
	if (KEYMANAGER->isOnceKeyDown('D')) 
	{
		if (player->isCatch == true)
		{
			player->dir = false;
			player->ChangeClip("two_hand_walk_right", false);

		}
		else
		{
			player->dir = false;
			player->ChangeClip("walk_right", false);

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
			player->ChangeClip("two_hand_walk_left", false);

		}
		else
		{
			player->dir = true;
			player->ChangeClip("walk_left", false);

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
		if (player->isCatch == false)
		{
			return new PlayerAttackState();
		}
		else
		{
			return new PlayerTwoHandAttackState();

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

	/*if (GROUNDMANAGER->CheckGround(player->playerBoxCheckRc) == 0)
	{
		return new PlayerFallState();
	}*/

	return nullptr;
}

void PlayerWalkState::Update(Player * player)
{
	
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

	//player->playerBoxCheckRc = RectMakeCenter(player->transform->GetX(), 
	//												player->transform->GetY()+55, 100, 4);

}

void PlayerWalkState::Enter(Player * player)
{
	if (player->isCatch == true)
	{
		if (player->dir == false)

			player->ChangeClip("two_hand_walk_right", false);
		else
			player->ChangeClip("two_hand_walk_left", false);
	}
	else
	{
		if (player->dir == false)
		{
			player->ChangeClip("walk_right", false);
		}
		else
		{
			player->ChangeClip("walk_left", false);
		}
	}
	


}

void PlayerWalkState::Exit(Player * player)
{
}
