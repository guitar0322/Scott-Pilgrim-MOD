#include "stdafx.h"
#include "PlayerWalkState.h"
#include "PlayerIdleState.h"
#include "PlayerRunState.h"
#include "PlayerJumpState.h"
#include "PlayerKickAttackState.h"
#include "PlayerAttackState.h"
#include "PlayerFallState.h"
#include "PlayerTwoHandAttackState.h"
#include "Player.h"

PlayerState * PlayerWalkState::InputHandle(Player * player)
{
	if (KEYMANAGER->isOnceKeyDown('D')) 
	{
		if (player->isCatch == true)
		{
			player->dir = false;
			player->ChangeClip("two_hand_walk_right", false);
		}
		else
		{
			player->dir = false;
			player->ChangeClip("walk_right", false);
		}
	
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		if (player->dir == true)
			player->runKeyPress = false;
		return new PlayerIdleState();
	}

	if (KEYMANAGER->isOnceKeyDown('A')) 
	{

		if (player->isCatch == true)
		{
			player->dir = true;
			player->ChangeClip("two_hand_walk_left", false);

		}
		else
		{
			player->dir = true;
			player->ChangeClip("walk_left", false);

		}
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		if (player->dir == false)
			player->runKeyPress = false;
		return new PlayerIdleState();
	}
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		player->runKeyPress = false;
		return new PlayerIdleState();
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		player->runKeyPress = false;
		return new PlayerIdleState();
	}

	if (KEYMANAGER->isStayKeyDown('J'))
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
		}
	}
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		if (player->dir == false)
		{
			return new PlayerKickAttackState();
		}
		else
		{
			return new PlayerKickAttackState();
		}
	}

	if (GROUNDMANAGER->CheckGround(player->groundCheckRc, player->zOrder->GetZ()) == 0 && player->onGround == true)
	{
		player->onGround = false;
		return new PlayerFallState();
	}

	return nullptr;
}

void PlayerWalkState::Update(Player * player)
{
	if (KEYMANAGER->isStayKeyDown('D') && player->dir == false) 
	{
		_itemShakeTime += TIMEMANAGER->getElapsedTime();
		if (_itemShakeTime >= 0.6f && player->isCatch == true)
		{
			if (_itemShakeDir == false)
				player->GetItemTransform()->Move(-1.5f,-2.2f);
			else
				player->GetItemTransform()->Move(1.5f, 2.2f);
			_itemShakeDir = !_itemShakeDir;
			_itemShakeTime = 0;
		}

		player->transform->MoveX(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('A') && player->dir == true)
	{
		_itemShakeTime += TIMEMANAGER->getElapsedTime();
		if (_itemShakeTime >= 0.6f && player->isCatch == true)
		{
			if (_itemShakeDir == false)
				player->GetItemTransform()->Move(-1.5f,-2.2f);
			else
				player->GetItemTransform()->Move(1.5f,2.2f);
			_itemShakeDir = !_itemShakeDir;
			_itemShakeTime = 0;
		}
		player->transform->MoveX(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->runKeyPress = false;
		player->zOrder->MoveZ(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->runKeyPress = false;
		player->zOrder->MoveZ(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}

	//player->playerBoxCheckRc = RectMakeCenter(player->transform->GetX(), 
	//												player->transform->GetY()+55, 100, 4);

}

void PlayerWalkState::Enter(Player * player)
{	
	_itemShakeTime = 0;

	if (player->isCatch == true)
	{
		if (player->dir == false)
		{
			player->GetItemTransform()->SetPosition(player->transform->GetX() - 14, player->transform->GetY() - 77);
			player->ChangeClip("two_hand_walk_right", false);
		}
		else
		{
			player->GetItemTransform()->SetPosition(player->transform->GetX() + 14, player->transform->GetY() - 77);
			player->ChangeClip("two_hand_walk_left", false);
		}
	}
	else
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
	


}

void PlayerWalkState::Exit(Player * player)
{
	if (_itemShakeDir == true)
	{
		player->GetItemTransform()->Move(-1.5f,-2.2f);
	}
}