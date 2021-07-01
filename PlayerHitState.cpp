#include "stdafx.h"
#include "PlayerHitState.h"

PlayerState * PlayerHitState::InputHandle(Player * player)
{
	return nullptr;
}

void PlayerHitState::Update(Player * player)
{




}

void PlayerHitState::Enter(Player * player)
{
}

void PlayerHitState::Exit(Player * player)
{
	if (player->dir == false)
	{
		player->ChangeClip("hit1_right", true);

	}
	else
	{
		player->ChangeClip("hit1_left", true);

	}

}
