#include "stdafx.h"
#include "PlayerGroundState.h"
#include "PlayerIdleState.h"
#include "Player.h"

PlayerState * PlayerGroundState::InputHandle(Player * player)
{
	if (player->groundZCheck == true && _jumpTime >= 0.4f)
	{
		player->jumpZ = false;
		player->groundZCheck = false;
		return new PlayerIdleState();
	}

	if (player->groundCheck == true && _jumpTime >= 0.7f) {
		player->groundCheck = false;
		return new PlayerIdleState();
	}

	return nullptr;
}

void PlayerGroundState::Update(Player * player)
{
	_jumpTime += TIMEMANAGER->getElapsedTime();
}

void PlayerGroundState::Enter(Player * player)
{
	_jumpTime = 0;
	player->dash = false;
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
