#include "stdafx.h"
#include "PlayerWalkState.h"
#include "PlayerIdleState.h"
#include "PlayerRunState.h"
#include "Player.h"

PlayerState * PlayerWalkState::InputHandle(Player * player)
{
	if (KEYMANAGER->isOnceKeyDown('D')) {
		player->dir = false;
		player->ChangeClip("walk_right", false);
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		return new PlayerIdleState();
	}

	if (KEYMANAGER->isOnceKeyDown('A')) {
		player->dir = true;
		player->ChangeClip("walk_left", false);
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		return new PlayerIdleState();
	}
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		return new PlayerIdleState();
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		return new PlayerIdleState();
	}

	return nullptr;
}

void PlayerWalkState::Update(Player * player)
{
	if (KEYMANAGER->isStayKeyDown('D') && player->dir == false) 
	{
		player->transform->MoveX(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
		player->ground->MoveX(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('A') && player->dir == true)
	{
		player->transform->MoveX(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
		player->ground->MoveX(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->dash = false;
		player->transform->MoveY(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
		player->ground->MoveY(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());

	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->dash = false;
		player->transform->MoveY(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
		player->ground->MoveY(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
}

void PlayerWalkState::Enter(Player * player)
{
	if (player->dir == false)
	{
		player->ChangeClip("walk_right", false);
	}
	else
	{
		player->ChangeClip("walk_left", false);
	}

}

void PlayerWalkState::Exit(Player * player)
{
}
