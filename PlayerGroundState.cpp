#include "stdafx.h"
#include "PlayerGroundState.h"
#include "PlayerIdleState.h"
#include "Player.h"

PlayerState * PlayerGroundState::InputHandle(Player * player)
{
	if (player->groundCheck == true && player->groundCheckDelay >= 0.6f)
	{
		player->groundCheck = false;
		player->groundCheckDelay = 0;
		return new PlayerIdleState();
	}
	if (_jumpTime > 0.5f)
	{
		player->jumpZ = false;
		player->groundZCheck = false;
		_jumpTime = 0;
		return new PlayerIdleState();
	}

	return nullptr;
}

void PlayerGroundState::Update(Player * player)
{
	if (player->groundZCheck == true && player->groundCheck == false)
	{
		_jumpTime += TIMEMANAGER->getElapsedTime();
	}
}

void PlayerGroundState::Enter(Player * player)
{
	_jumpTime = 0;

	if (player->dir == false)
	{
		player->ChangeClip("ground_right", false);
	}
	else
	{
		player->ChangeClip("ground_left", false);
	}

}

void PlayerGroundState::Exit(Player * player)
{
}
