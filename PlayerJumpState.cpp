#include "stdafx.h"
#include "PlayerJumpState.h"
#include "PlayerIdleState.h"
#include "PlayerGroundState.h"
#include "PlayerFallState.h"
#include "PlayerJumpKickState.h"
#include "Player.h"

PlayerState * PlayerJumpState::InputHandle(Player * player)
{
	if (_jumpPower < 0)
	{
		return new PlayerFallState();

	}
	if (player->animator->currentFrame == player->animator->curClip->frameNum - 1)
	{
		if (KEYMANAGER->isOnceKeyDown('L'))
		{
			return new PlayerJumpKickState();

		}

	}
	//점프 L 날라차기
	
	return nullptr;
}

void PlayerJumpState::Update(Player * player)
{
	_jumpPower -= player->GetGravity()*TIMEMANAGER->getElapsedTime();
	player->transform->MoveY(-_jumpPower * TIMEMANAGER->getElapsedTime());
	


	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (player->isRun == true) //뛸 때 -> 점프
		{
			player->transform->MoveX(player->GetSpeed()*2 *TIMEMANAGER->getElapsedTime());
			player->ground->MoveX(player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime());
		}
		else // 안 뒬 때 -> 점프
		{
			player->transform->MoveX(player->GetSpeed()*1.5f*TIMEMANAGER->getElapsedTime());
			player->ground->MoveX(player->GetSpeed()*1.5f* TIMEMANAGER->getElapsedTime());

		}
		
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (player->isRun == true)
		{
			player->transform->MoveX(-player->GetSpeed() * 2 *TIMEMANAGER->getElapsedTime());
			player->ground->MoveX(-player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime());

			
		}
		else
		{
			player->transform->MoveX(-player->GetSpeed()*1.5f*TIMEMANAGER->getElapsedTime());
			player->ground->MoveX(-player->GetSpeed() *1.5f* TIMEMANAGER->getElapsedTime());

		}
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->ground->MoveY(-player->GetSpeed() *0.7f* TIMEMANAGER->getElapsedTime());
		player->zOrder->MoveZ(-player->GetSpeed() *0.7f* TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->ground->MoveY(player->GetSpeed() *0.7f* TIMEMANAGER->getElapsedTime());
		player->zOrder->MoveZ(player->GetSpeed() *0.7f* TIMEMANAGER->getElapsedTime());

	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player->ChangeClip("jump_right", true);
		player->dir = false;
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		player->ChangeClip("jump_left", true);
		player->dir = true;
	}

	

}

void PlayerJumpState::Enter(Player * player)
{
	_jumpPower = 200;
	if (player->dir == false)
	{
		player->ChangeClip("jump_right", false);
	}
	else
	{
		player->ChangeClip("jump_left", false);
	}
}

void PlayerJumpState::Exit(Player * player)
{
}
