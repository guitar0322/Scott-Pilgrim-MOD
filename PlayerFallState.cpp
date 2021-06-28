#include "stdafx.h"
#include "PlayerFallState.h"
#include "PlayerGroundState.h"
#include "Player.h"

PlayerState * PlayerFallState::InputHandle(Player * player)
{
	int intersectHeight = GROUNDMANAGER->CheckGround(player->collider->rc, player->zOrder->GetZ());
	if (intersectHeight != 0)
	{
		player->groundCheck = true;

		player->transform->MoveY(-intersectHeight);
		player->onGround = true;
		return new PlayerGroundState();
	}

	if (player->transform->GetY() + 52 >= player->zOrder->GetZ()) {
		player->groundCheck = true;
		return new PlayerGroundState();
	}
	return nullptr;
}

void PlayerFallState::Update(Player * player)
{
	//중력값을 올려서 좀 더 빨리 떨어지는 효과를 보여줌
	_speedY += player->GetGravity()*TIMEMANAGER->getElapsedTime();

	player->transform->MoveY(_speedY * TIMEMANAGER->getElapsedTime());

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		player->transform->MoveX(player->GetSpeed() * TIMEMANAGER->getElapsedTime());

	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->transform->MoveX(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());

	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->zOrder->MoveZ(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());

	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->zOrder->MoveZ(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
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
