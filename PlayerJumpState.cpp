#include "stdafx.h"
#include "PlayerJumpState.h"
#include "PlayerIdleState.h"
#include "PlayerGroundState.h"
#include "PlayerFallState.h"
#include "PlayerJumpKickState.h"
#include "Player.h"

PlayerState * PlayerJumpState::InputHandle(Player * player)
{
	if (player->jumpPower < 0)
	{
		return new PlayerFallState();
	}
	
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		return new PlayerJumpKickState();
	}


	
	//점프 L 날라차기
	
	
	return nullptr;
}

void PlayerJumpState::Update(Player * player)
{
	player->jumpPower -= player->GetGravity()*TIMEMANAGER->getElapsedTime();
	player->transform->MoveY(-player->jumpPower * TIMEMANAGER->getElapsedTime());

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (player->isRun == true) //뛸 때 -> 점프
		{
			player->transform->MoveX(player->GetSpeed()* 2 *TIMEMANAGER->getElapsedTime());
		}
		else // 안 뒬 때 -> 점프
		{
			player->transform->MoveX(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
		}
		
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (player->isRun == true)
		{
			player->transform->MoveX(-player->GetSpeed() * 2 *TIMEMANAGER->getElapsedTime());
		}
		else
		{
			player->transform->MoveX(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
		}
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->zOrder->MoveZ(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->zOrder->MoveZ(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (player->isCatch == true)
		{
			player->dir = false;
			player->ChangeClip("two_hand_jump_right", false);
		}
		else
		{
			player->dir = false;
			player->ChangeClip("jump_right", true);
		}
		
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (player->isCatch == true)
		{
			player->dir = true;
			player->ChangeClip("two_hand_jump_left", false);
		}
		else
		{
			player->dir = true;
			player->ChangeClip("jump_left", true);
		}
	
	}

	

}

void PlayerJumpState::Enter(Player * player)
{
	player->jumpPower = 200;

	if (player->isCatch == true)
	{
		if (player->dir == false)
		{
			player->ChangeClip("two_hand_jump_right", false);
		}
		else
		{
			player->ChangeClip("two_hand_jump_left", false);

		}
	}
	else
	{
		if (player->dir == false)
		{
			player->ChangeClip("jump_right", false);
		}
		else
		{
			player->ChangeClip("jump_left", false);
		}
	}
	
}

void PlayerJumpState::Exit(Player * player)
{
}
