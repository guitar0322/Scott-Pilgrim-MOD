#include "stdafx.h"
#include "PlayerFallState.h"
#include "PlayerGroundState.h"
#include "PlayerJumpKickState.h"
#include "Player.h"

PlayerState * PlayerFallState::InputHandle(Player * player)
{
	int intersectHeight = GROUNDMANAGER->CheckGround(player->collider->rc, player->zOrder->GetZ());
	if (intersectHeight != 0)
	{
		player->groundCheck = true;

		player->transform->MoveY(-intersectHeight);
		player->onGround = true;
		return new PlayerGroundState();
	}

	if (player->transform->GetY() + 52 >= player->zOrder->GetZ()) {
		player->groundCheck = true;
		return new PlayerGroundState();
	}

	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		return new PlayerJumpKickState();

	}
	return nullptr;
}

void PlayerFallState::Update(Player * player)
{
	//중력값을 올려서 좀 더 빨리 떨어지는 효과를 보여줌
	_speedY += player->GetGravity()*TIMEMANAGER->getElapsedTime();

	player->transform->MoveY(_speedY * TIMEMANAGER->getElapsedTime());

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (player->isRun == true) //뛸 때 -> 점프
		{
			player->transform->MoveX(player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime());

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
			player->transform->MoveX(-player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime());
		}
		else
		{
			player->transform->MoveX(-player->GetSpeed()*TIMEMANAGER->getElapsedTime());
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
			player->ChangeClip("two_hand_fall_right", false);

		}
		else
		{
			player->dir = false;
			player->ChangeClip("fall_right", true);

		}
	
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (player->isCatch == true)
		{
			player->dir = true;
			player->ChangeClip("two_hand_fall_left", false);

		}
		else
		{
			player->dir = true;
			player->ChangeClip("fall_left", true);

		}
	
	}

}

void PlayerFallState::Enter(Player * player)
{
	_speedY = 0;
	if (player->isCatch == true)
	{
		if (player->dir == false)
		{
			player->ChangeClip("two_hand_fall_right", false);
		}
		else
		{
			player->ChangeClip("two_hand_fall_left", false);
		}
	}
	else
	{
		if (player->dir == false)
		{
			player->ChangeClip("fall_right", false);
		}
		else
		{
			player->ChangeClip("fall_left", false);
		}
	}

	
}

void PlayerFallState::Exit(Player * player)
{
	
}
