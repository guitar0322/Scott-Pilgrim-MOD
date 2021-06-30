#include "stdafx.h"
#include "PlayerTwoHandAttackState.h"
#include "PlayerIdleState.h"
#include "Player.h"

PlayerState * PlayerTwoHandAttackState::InputHandle(Player * player)
{
	if (player->animator->GetEnd())
	{
		return new PlayerIdleState();
	}
	return nullptr;
}

void PlayerTwoHandAttackState::Update(Player * player)
{
}

void PlayerTwoHandAttackState::Enter(Player * player)
{

	if (player->isRun == false)
	{
		if (player->dir == false)
			player->ChangeClip("two_hand_walk_attack_right", false);
		else
			player->ChangeClip("two_hand_walk_attack_left", false);
	}
	else
	{
		player->isRun = false;

		if (player->dir == false)
			player->ChangeClip("two_hand_run_attack_right", false);
		else
			player->ChangeClip("two_hand_run_attack_left", false);
	}

}

void PlayerTwoHandAttackState::Exit(Player * player)
{

}
