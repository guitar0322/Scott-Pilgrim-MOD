#include "stdafx.h"
#include "PlayerFallState.h"
#include "PlayerGroundState.h"
#include "Player.h"

PlayerState * PlayerFallState::InputHandle(Player * player)
{
	int intersectHeight = GROUNDMANAGER->CheckGround(player->collider->rc);
	if (intersectHeight != 0)
	{
		player->groundCheck = true;
		player->transform->MoveY(-intersectHeight);
		return new PlayerGroundState();
	}

	return nullptr;
}

void PlayerFallState::Update(Player * player)
{
	_speedY += player->GetGravity()*TIMEMANAGER->getElapsedTime() * 4.5;

	player->transform->MoveY(_speedY * TIMEMANAGER->getElapsedTime());


	if (KEYMANAGER->isStayKeyDown('D'))
	{
		player->dash = false;
		player->transform->MoveX(player->GetSpeed()*0.6*TIMEMANAGER->getElapsedTime());
		player->ground->MoveX(player->GetSpeed()*0.6 * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->dash = false;

		player->transform->MoveX(-player->GetSpeed()*0.6*TIMEMANAGER->getElapsedTime());
		player->ground->MoveX(-player->GetSpeed()*0.6 * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->dash = false;

		player->transform->MoveY(-player->GetSpeed()*0.6*TIMEMANAGER->getElapsedTime());
		player->ground->MoveY(-player->GetSpeed()* 0.6 * TIMEMANAGER->getElapsedTime());
		player->zOrder->MoveY(-player->GetSpeed()* 0.6 * TIMEMANAGER->getElapsedTime());

	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->dash = false;

		player->transform->MoveY(player->GetSpeed()*0.6*TIMEMANAGER->getElapsedTime());
		player->ground->MoveY(player->GetSpeed()*0.6 * TIMEMANAGER->getElapsedTime());
		player->zOrder->MoveY(player->GetSpeed()* 0.6 * TIMEMANAGER->getElapsedTime());

	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player->ChangeClip("fall_right", true);
		player->dir = false;
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		player->ChangeClip("fall_left", true);
		player->dir = true;

	}

}

void PlayerFallState::Enter(Player * player)
{
	_speedY = 0;

	if (player->dir == false)
	{
		player->ChangeClip("fall_right", false);
	}
	else
	{
		player->ChangeClip("fall_left", false);
	}
}

void PlayerFallState::Exit(Player * player)
{
	
}
