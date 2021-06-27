#include "stdafx.h"
#include "PlayerJumpKickState.h"
#include "PlayerIdleState.h"
#include "Player.h"

PlayerState * PlayerJumpKickState::InputHandle(Player * player)
{
	int intersectHeight = GROUNDMANAGER->CheckGround(player->collider->rc);
	if (intersectHeight != 0)
	{

		player->transform->MoveY(-intersectHeight);
		return new PlayerIdleState();
	}

	


	return nullptr;
}

void PlayerJumpKickState::Update(Player* player)
{
	_speedY += player->GetGravity()*TIMEMANAGER->getElapsedTime()*2;

	player->transform->MoveY(_speedY * TIMEMANAGER->getElapsedTime());

	
}

void PlayerJumpKickState::Enter(Player* player)
{
	
	if (player->isRun == false)
	{
		if (player->dir == false)
		{
			player->ChangeClip("walk_jump_kick_right", false);
		}
		else
		{
			player->ChangeClip("walk_jump_kick_left", false);
		}
	}
	else
	{
		if (player->dir == false)
		{
			player->ChangeClip("run_jump_kick_right", false);
		}
		else
		{
			player->ChangeClip("run_jump_kick_left", false);
		}
	}


}

void PlayerJumpKickState::Exit(Player* player)
{
	

}
