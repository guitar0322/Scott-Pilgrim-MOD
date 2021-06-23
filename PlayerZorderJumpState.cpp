#include "stdafx.h"
#include "PlayerZorderJumpState.h"

PlayerState * PlayerZorderJumpState::InputHandle(Player * player)
{
	
	if (GROUNDMANAGER->CheckGround(player->collider->rc) == true)
	{
	
		return new PlayerIdleState();
	}
	
	

	return nullptr;
}

void PlayerZorderJumpState::Update(Player * player)
{
	_jumpPowerZorder -= player->GetGravity()*TIMEMANAGER->getElapsedTime() *2;

	if (player->dirZ == true)
	{

		player->transform->MoveY(-_speedZ * TIMEMANAGER->getElapsedTime());
		player->transform->MoveY(-_jumpPowerZorder *0.5 *TIMEMANAGER->getElapsedTime());

		player->ground->MoveY(-_speedZ * TIMEMANAGER->getElapsedTime());
		player->groundCheck = false;
		_jumpPowerZorder = 0;


	}
	else
	{
		player->transform->MoveY(_speedZ * TIMEMANAGER->getElapsedTime());
		player->transform->MoveY(-_jumpPowerZorder * 0.5* TIMEMANAGER->getElapsedTime());

		player->ground->MoveY(_speedZ * TIMEMANAGER->getElapsedTime());
		player->groundCheck = false;
		_jumpPowerZorder = 0;
	
	}
	
	
}

void PlayerZorderJumpState::Enter(Player * player)
{
	_jumpPowerZorder = 100;
	_speedZ = 100;
	player->groundCheck = true;

	if (player->dir == false)
	{
		player->ChangeClip("jumpZorder_right", false);
	}
	else
	{
		player->ChangeClip("jumpZorder_left", false);
	}
}

void PlayerZorderJumpState::Exit(Player * player)
{
}
