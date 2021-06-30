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
	player->jumpPower -= player->GetGravity()*TIMEMANAGER->getElapsedTime();

	if (player->jumpPower < 0)
	{
		player->transform->MoveY(-player->jumpPower * TIMEMANAGER->getElapsedTime());
	}

	if (player->isRun == true)
	{
		player->transform->MoveX(player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime());
	}
}

void PlayerJumpKickState::Enter(Player* player)
{
	if (player->isRun == false)
	{
		if (player->dir == false)
		{
			player->ChangeClip("walk_jump_kick_right", false);
		}
		else
		{
			player->ChangeClip("walk_jump_kick_left", false);
		}
	}
	else
	{
		if (player->dir == false)
		{
			player->ChangeClip("run_jump_kick_right", false);
		}
		else
		{
			player->ChangeClip("run_jump_kick_left", false);
		}
	}
}

void PlayerJumpKickState::Exit(Player* player)
{

}
