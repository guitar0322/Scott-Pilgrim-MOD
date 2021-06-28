#include "stdafx.h"
#include "PlayerKickSkillState.h"
#include "PlayerIdleState.h"
#include "Player.h"

PlayerState * PlayerKickSkillState::InputHandle(Player * player)
{
	if (player->animator->currentFrame == player->animator->curClip->frameNum - 1)
	{
		return new PlayerIdleState();
	}

	return nullptr;
}

void PlayerKickSkillState::Update(Player * player)
{
}

void PlayerKickSkillState::Enter(Player * player)
{
	if (player->dir == false)
	{
		player->ChangeClip("kick_skill_right", false);
	}
	else
	{
		player->ChangeClip("kick_skill_left", false);
	}

}

void PlayerKickSkillState::Exit(Player * palyer)
{
}
