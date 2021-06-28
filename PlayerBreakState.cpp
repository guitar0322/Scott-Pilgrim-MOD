#include "stdafx.h"
#include "PlayerBreakState.h"
#include "PlayerIdleState.h"
#include "player.h"

PlayerState * PlayerBreakState::InputHandle(Player * player)
{
	if (_dashSpeed < 0)
	{
		return new PlayerIdleState();
	}
	return nullptr;
}

void PlayerBreakState::Update(Player * player)
{
	_dashSpeed -= player->GetFriction() * TIMEMANAGER->getElapsedTime();
	if (player->dir == false)
	{
		player->transform->MoveX(_dashSpeed * TIMEMANAGER->getElapsedTime());
	}
	else
	{
		player->transform->MoveX(-_dashSpeed * TIMEMANAGER->getElapsedTime());
	}
}

void PlayerBreakState::Enter(Player * player)
{
	_dashSpeed = 80;
	if (player->dir == false)
	{
		player->ChangeClip("idle_right", false);
	}
	else
	{
		player->ChangeClip("idle_left", false);
	}
}

void PlayerBreakState::Exit(Player * player)
{
	


}
