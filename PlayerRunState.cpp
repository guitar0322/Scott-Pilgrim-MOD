#include "stdafx.h"
#include "PlayerRunState.h"
#include "PlayerBreakState.h"
#include "PlayerJumpState.h"
#include "PlayerKickAttackState.h"
#include "PlayerAttackState.h"
#include "PlayerTwoHandAttackState.h"
#include "Player.h"

PlayerState * PlayerRunState::InputHandle(Player * player)
{
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		return new PlayerBreakState();
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		return new PlayerBreakState();
	}

	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		return new PlayerJumpState();
	}

	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		if (player->isCatch == false)
		{
			return new PlayerAttackState();
		}
		else
		{
			return new PlayerTwoHandAttackState();
;		}
	}
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		return new PlayerKickAttackState();

	}

	return nullptr;
}

void PlayerRunState::Update(Player * player)
{
	if (player->dir == false)
	{
		if (player->isCatch == true)
			_itemShakeTime += TIMEMANAGER->getElapsedTime();
		if (_itemShakeTime >= 0.415f)
		{
			if(_itemShakeDir == false)
				player->GetItemTransform()->Move(-5, -6.5f);
			else player->GetItemTransform()->Move(5, 6.5f);
			_itemShakeDir = !_itemShakeDir;
			_itemShakeTime = 0;
		}
		player->transform->MoveX(player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime());
	}
	else
	{
		if (player->isCatch == true)
			_itemShakeTime += TIMEMANAGER->getElapsedTime();
		if (_itemShakeTime >= 0.6f)
		{
			if (_itemShakeDir == false)
				player->GetItemTransform()->Move(-5, -6.5f);
			else player->GetItemTransform()->Move(5, 6.5f);
			_itemShakeDir = !_itemShakeDir;
			_itemShakeTime = 0;
		}
		player->transform->MoveX(-player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime());
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->zOrder->MoveZ(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->zOrder->MoveZ(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}

	
	

}

void PlayerRunState::Enter(Player * player)
{
	_itemShakeTime = 0;
	if (player->isCatch == true)
	{
		if (player->dir == false)
		{
			player->GetItemTransform()->SetPosition(player->transform->GetX() - 38, player->transform->GetY() - 77);
			player->ChangeClip("two_hand_run_right", false);
		}
		else
		{
			player->GetItemTransform()->SetPosition(player->transform->GetX() + 38, player->transform->GetY() - 77);
			player->ChangeClip("two_hand_run_left", false);
		}
	}
	else
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
	
}

void PlayerRunState::Exit(Player * player)
{
	if (_itemShakeDir == true)
	{
		player->GetItemTransform()->Move(-1, 2.5f);
	}
}
