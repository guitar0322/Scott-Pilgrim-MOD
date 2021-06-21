#include "stdafx.h"
#include "PlayerRunState.h"
#include "PlayerIdleState.h"
#include "Player.h"

PlayerState * PlayerRunState::InputHandle(Player * player)
{
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		return new PlayerIdleState();
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		return new PlayerIdleState();
	}

	return nullptr;
}

void PlayerRunState::Update(Player * player)
{
	if (player->dir == false)
	{
		player->transform->MoveX(player->GetSpeed() * 1.5 * TIMEMANAGER->getElapsedTime());
		player->ground->MoveX(player->GetSpeed() * 1.5 * TIMEMANAGER->getElapsedTime());
	}
	else
	{
		player->transform->MoveX(-player->GetSpeed() * 1.5 * TIMEMANAGER->getElapsedTime());
		player->ground->MoveX(-player->GetSpeed() * 1.5 * TIMEMANAGER->getElapsedTime());
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->transform->MoveY(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
		player->ground->MoveY(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());


	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->transform->MoveY(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
		player->ground->MoveY(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}

}

void PlayerRunState::Enter(Player * player)
{
	if (player->dir == false)
	{
		player->ChangeClip("run_right", false);
	}
	else
	{
		player->ChangeClip("run_left", false);
	}
}

void PlayerRunState::Exit(Player * player)
{
}
