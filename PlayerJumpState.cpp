#include "stdafx.h"
#include "PlayerJumpState.h"
#include "PlayerIdleState.h"
#include "PlayerGroundState.h"
#include "PlayerFallState.h"
#include "Player.h"

PlayerState * PlayerJumpState::InputHandle(Player * player)
{
	if (_jumpPower < 0)
	{
		return new PlayerFallState;
	}
	
	return nullptr;
}

void PlayerJumpState::Update(Player * player)
{
	_jumpPower -= player->GetGravity()*TIMEMANAGER->getElapsedTime();

	player->transform->MoveY(-_jumpPower * TIMEMANAGER->getElapsedTime());


	if (KEYMANAGER->isStayKeyDown('D'))
	{
		player->dashStop = false;
		player->transform->MoveX(player->GetSpeed()*0.6*TIMEMANAGER->getElapsedTime());
		player->ground->MoveX(player->GetSpeed()*0.6 * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->dashStop = false;
		player->transform->MoveX(-player->GetSpeed()*0.6*TIMEMANAGER->getElapsedTime());
		player->ground->MoveX(-player->GetSpeed()*0.6 * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->dashStop = false;

		player->transform->MoveY(-player->GetSpeed()*0.3*TIMEMANAGER->getElapsedTime());
		player->ground->MoveY(-player->GetSpeed()* 0.3 * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->dashStop = false;

		player->transform->MoveY(player->GetSpeed()*0.3*TIMEMANAGER->getElapsedTime());
		player->ground->MoveY(player->GetSpeed()*0.3 * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player->ChangeClip("jump_right", true);
		player->dir = false;
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		player->ChangeClip("jump_left", true);
		player->dir = true;

	}


}

void PlayerJumpState::Enter(Player * player)
{
	_jumpPower = 170;

	if (player->dir == false)
	{
		player->ChangeClip("jump_right", false);
	}
	else
	{
		player->ChangeClip("jump_left", false);
	}

}

void PlayerJumpState::Exit(Player * player)
{
}
