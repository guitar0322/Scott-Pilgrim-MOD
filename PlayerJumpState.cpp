#include "stdafx.h"
#include "PlayerJumpState.h"
#include "PlayerIdleState.h"
#include "Player.h"

PlayerState * PlayerJumpState::InputHandle(Player * player)
{
	//if (player->transform->GetY() > WINSIZEY / 2)
	//{
	//	return new PlayerIdleState();

	//}
	if (GROUNDMANAGER->CheckGround(player->collider->rc) == true) 
	{
		return new PlayerIdleState();
	}
	return nullptr;
}

void PlayerJumpState::Update(Player * player)
{
	_jumpPower -= player->GetGravity()*TIMEMANAGER->getElapsedTime();

	player->transform->MoveY(-_jumpPower * TIMEMANAGER->getElapsedTime());

	//_count++;

	//if (_count % 20 == 0)
	//{
	//	_jumpPower += player->GetGravity()*TIMEMANAGER->getElapsedTime();

	//	player->transform->MoveY(_jumpPower * TIMEMANAGER->getElapsedTime());

	//}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		player->transform->MoveX(player->GetSpeed()*TIMEMANAGER->getElapsedTime());
		player->ground->MoveX(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->transform->MoveX(-player->GetSpeed()*TIMEMANAGER->getElapsedTime());
		player->ground->MoveX(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->transform->MoveY(-player->GetSpeed()*TIMEMANAGER->getElapsedTime());
		player->ground->MoveY(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->transform->MoveY(player->GetSpeed()*TIMEMANAGER->getElapsedTime());
		player->ground->MoveY(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
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
	_jumpPower = 150;

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
