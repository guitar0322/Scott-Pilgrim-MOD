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
			player->ChangeClip("two_hand_walk_right", true);
		}
		else
		{
			player->dir = false;
			player->ChangeClip("walk_right", true);
		}
	}
	if (KEYMANAGER->isOnceKeyUp('D') && !KEYMANAGER->isStayKeyDown('W') && !KEYMANAGER->isStayKeyDown('S'))
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
		}
		else
		{
			player->dir = true;
			player->ChangeClip("walk_left", true);
		}
	}
	if (KEYMANAGER->isOnceKeyUp('A') && !KEYMANAGER->isStayKeyDown('W') && !KEYMANAGER->isStayKeyDown('S'))
	{
		if (player->dir == false)
			player->runKeyPress = false;
		return new PlayerIdleState();
	}
	if (KEYMANAGER->isOnceKeyUp('W') && !KEYMANAGER->isStayKeyDown('D') && !KEYMANAGER->isStayKeyDown('A'))
	{
		return new PlayerIdleState();
	}
	if (KEYMANAGER->isOnceKeyUp('S') && !KEYMANAGER->isStayKeyDown('D') && !KEYMANAGER->isStayKeyDown('A'))
	{
		return new PlayerIdleState();
	}

	if (KEYMANAGER->isStayKeyDown('J'))
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

	if (GROUNDMANAGER->CheckGround(player->groundCheckRc, player->zOrder->GetZ()) == 0 && player->onGround == true)
	{
		player->onGround = false;
		return new PlayerFallState();
	}

	if (player->zOrder->GetZ() == 1000)
	{
		return new PlayerFallState();
	}
	return nullptr;
}

void PlayerWalkState::Update(Player * player)
{
	if (KEYMANAGER->isStayKeyDown('D') && player->dir == false) 
	{
		player->transform->MoveX(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
		if (MAPMANAGER->IsInSlope1(player->gameObject) == true) {
			player->zOrder->MoveZ(player->GetSpeed() * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
			MainCam->transform->MoveY(player->GetSpeed() * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
		}
	}
	if (KEYMANAGER->isStayKeyDown('A') && player->dir == true)
	{
		player->transform->MoveX(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
		if (MAPMANAGER->IsInSlope1(player->gameObject) == true) {
			player->zOrder->MoveZ(-player->GetSpeed() * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
			MainCam->transform->MoveY(-player->GetSpeed() * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
		}
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

void PlayerWalkState::Enter(Player * player)
{
	if (player->isCatch == true)
	{
		if (player->dir == false)

			player->ChangeClip("two_hand_walk_right", true);
		else
			player->ChangeClip("two_hand_walk_left", true);
	}
	else
	{
		if (player->dir == false)
		{
			player->ChangeClip("walk_right", true);
		}
		else
		{
			player->ChangeClip("walk_left", true);
		}
	}
}

void PlayerWalkState::Exit(Player * player)
{
}
