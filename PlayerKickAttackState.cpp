#include "stdafx.h"
#include "PlayerKickAttackState.h"
#include "PlayerIdleState.h"
#include "PlayerGroundState.h"
#include "Player.h"

PlayerState * PlayerKickAttackState::InputHandle(Player * player)
{
	
	if (player->animator->GetEnd())
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
		player->ChangeClip("kick_attack_right", true);
	}
	else
	{
		player->ChangeClip("kick_attack_left", true);
	}

}


void PlayerKickAttackState::Exit(Player * player)
{
}
