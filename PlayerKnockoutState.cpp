#include "stdafx.h"
#include "PlayerKnockoutState.h"
#include "PlayerIdleState.h"

PlayerState* PlayerKnockoutState::InputHandle(Player* player)
{
	if (_knockoutTime >= 4.f) {
		return new PlayerIdleState();
	}
	return nullptr;
}

void PlayerKnockoutState::Update(Player* player)
{
	_knockoutTime += TIMEMANAGER->getElapsedTime();
}

void PlayerKnockoutState::Enter(Player* player)
{
	player->jumpPower = 0;
	_knockoutTime = 0;
	if (player->dir == false)
	{
		player->ChangeClip("knockout_right", true);
	}
	else
	{
		player->ChangeClip("knockout_left", true);
	}
}

void PlayerKnockoutState::Exit(Player* player)
{
	player->hitable = true;
	player->transform->MoveY(-10);

}
