#include "stdafx.h"
#include "PlayerKickSkillState.h"
#include "PlayerIdleState.h"
#include "Player.h"

PlayerState * PlayerKickSkillState::InputHandle(Player * player)
{
	if (player->animator->GetEnd())
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
		player->ChangeClip("kick_skill_right", true);
	}
	else
	{
		player->ChangeClip("kick_skill_left", true);
	}

}

void PlayerKickSkillState::Exit(Player * palyer)
{
}
