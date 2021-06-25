#include "stdafx.h"
#include "PlayerShieldState.h"
#include "PlayerIdleState.h"
#include "Player.h"

PlayerState * PlayerShieldState::InputHandle(Player * player)
{
	
	if (player->animator->currentFrame == player->animator->curClip->frameNum-1)
	{
		return new PlayerIdleState();
	}
	return nullptr;
}

void PlayerShieldState::Update(Player * player)
{
	if (player->animator->currentFrame >= 4)
	{
		player->animator->Pause();
	}

	if (KEYMANAGER->isOnceKeyUp('K'))
	{
		player->block = false;	
	}

	if (player->block == false)
	{
		player->animator->Resume();
	}
}

void PlayerShieldState::Enter(Player * player)
{
	if (player->dir == false)
	{
		player->ChangeClip("shield_right", false);
	}
	else
	{
		player->ChangeClip("shield_left", false);
	}
}

void PlayerShieldState::Exit(Player * player)
{
}
