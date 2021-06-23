#include "stdafx.h"
#include "PlayerKickAttackState.h"
#include "PlayerIdleState.h"
#include "Player.h"

PlayerState * PlayerKickAttackState::InputHandle(Player * player)
{
	
	if (player->animator->currentFrame == player->animator->curClip->frameNum - 1)
	{
		return new PlayerIdleState();
	}

	return nullptr;
}

void PlayerKickAttackState::Update(Player * player)
{
}

void PlayerKickAttackState::Enter(Player * player)
{
	if (player->dir == false)
	{
		player->ChangeClip("kickAttack_right", false);
	}
	else
	{
		player->ChangeClip("kickAttack_left", false);
	}

}


void PlayerKickAttackState::Exit(Player * player)
{
}
