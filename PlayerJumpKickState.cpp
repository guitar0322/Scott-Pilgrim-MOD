#include "stdafx.h"
#include "PlayerJumpKickState.h"
#include "PlayerIdleState.h"
#include "Player.h"

PlayerState * PlayerJumpKickState::InputHandle(Player * player)
{
	int intersectHeight = GROUNDMANAGER->CheckGround(player->collider->rc, player->zOrder->GetZ());
	if (intersectHeight != 0)
	{
		player->transform->MoveY(-intersectHeight);
		player->onGround = true;
		return new PlayerIdleState();
	}
	if (player->transform->GetY() + 52 >= player->zOrder->GetZ()) {
		return new PlayerIdleState();
	}

	return nullptr;
}

void PlayerJumpKickState::Update(Player* player)
{
	player->jumpPower += player->GetGravity()*TIMEMANAGER->getElapsedTime();
	player->transform->MoveY(player->jumpPower * TIMEMANAGER->getElapsedTime());

	if (player->isRun == true)
	{
		if (player->dir == false)
		{
			player->transform->MoveX(player->GetSpeed() * 2.5f * TIMEMANAGER->getElapsedTime());
		}
		else
		{
			player->transform->MoveX(-player->GetSpeed() * 2.5f * TIMEMANAGER->getElapsedTime());
		}
	}
	
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (player->isRun == false)
			player->transform->MoveX(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (player->isRun == false)
			player->transform->MoveX(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
}

void PlayerJumpKickState::Enter(Player* player)
{
	player->jumpPower = 0;

	if (player->isRun == false)
	{
		if (player->dir == false)
		{
			player->ChangeClip("walk_jump_kick_right", true);
		}
		else
		{
			player->ChangeClip("walk_jump_kick_left", true);
		}
	}
	else
	{
		if (player->dir == false)
		{
			player->ChangeClip("run_jump_kick_right", true);
		}
		else
		{
			player->ChangeClip("run_jump_kick_left", true);
		}
	}
}

void PlayerJumpKickState::Exit(Player* player)
{

}
