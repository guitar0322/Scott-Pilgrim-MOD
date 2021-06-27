#include "stdafx.h"
#include "PlayerZorderJumpState.h"
#include "PlayerIdleState.h"
#include "PlayerGroundState.h"
#include "Player.h"

PlayerState * PlayerZorderJumpState::InputHandle(Player * player)
{
	int intersectHeight = GROUNDMANAGER->CheckGround(player->collider->rc);
	if (intersectHeight != 0)
	{
		player->jumpZ = true;
		player->transform->MoveY(-intersectHeight);
		return new PlayerGroundState();
	}
	return nullptr;
}

void PlayerZorderJumpState::Update(Player * player)
{
	_jumpPower -= player->GetGravity()*TIMEMANAGER->getElapsedTime() * 2;

	if (player->dirZ == true)
	{
		player->zOrder->MoveZ(-_speedZ * TIMEMANAGER->getElapsedTime());
		player->ground->MoveY(-_speedZ * TIMEMANAGER->getElapsedTime());

		player->transform->MoveY(-_jumpPower * TIMEMANAGER->getElapsedTime());
	}
	else
	{
		player->zOrder->MoveZ(_speedZ * TIMEMANAGER->getElapsedTime());
		player->ground->MoveY(_speedZ * TIMEMANAGER->getElapsedTime());

		player->transform->MoveY(-_jumpPower * TIMEMANAGER->getElapsedTime());
	}
}

void PlayerZorderJumpState::Enter(Player * player)
{
	_jumpPower = 80;
	_speedZ = 70;

	if (player->dir == false)
	{
		player->ChangeClip("jump_Zorder_right", false);
	}
	else
	{
		player->ChangeClip("jump_Zorder_left", false);
	}
}

void PlayerZorderJumpState::Exit(Player * player)
{
}
