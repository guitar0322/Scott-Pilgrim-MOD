#include "stdafx.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerJumpState.h"
#include "PlayerZorderJumpState.h"
#include "PlayerRunState.h"
#include "PlayerAttackState.h"
#include "PlayerBlockState.h"
#include "PlayerKickAttackState.h"
#include "PlayerKickSkillState.h"
#include "Player.h"

PlayerState * PlayerIdleState::InputHandle(Player * player)
{
	//좌우 걷기 모드
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		//두번 눌렀을 때 run 상태로 변경
		if (player->dir == false && player->runDelay <= 0.5f && player->runKeyPress == true) {
			player->dir = false;
			player->runKeyPress = false;
			player->isRun = true;

			player->runDelay = 0;
			return new PlayerRunState();
		}
		/*
		if (player->dir == false && player->isCatch == true)
		{
			player->dir = false;



		}
		*/
		//플레이어 오른쪽 걷기
		player->dir = false;
		player->runKeyPress = true;
		player->runDelay = 0;
		player->isRun = false;


		return new PlayerWalkState();
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (player->dir == true && player->runDelay <= 0.5f && player->runKeyPress == true) {
			player->dir = true;
			player->runKeyPress = false;
			player->isRun = true;


			player->runDelay = 0;
			return new PlayerRunState();
		}
		//플레이어 왼쪽
		player->dir = true;
		player->runKeyPress = true;
		player->runDelay = 0;
		player->isRun = false;


		return new PlayerWalkState();

	}
	//위 아래 걷기 모드
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (player->dir == true && player->jumpDelay <= 0.7f && player->jumpZ == true)
		{
			player->dir = true;
			player->jumpZ = false;
			player->dirZ = true;
			player->groundZCheck = true;
			player->groundCheck = false;

			player->jumpDelay = 0;
			return new PlayerZorderJumpState();
		}
		if (player->dir == false && player->jumpDelay <= 0.7f && player->jumpZ == true)
		{
			player->dir = false;
			player->jumpZ = false;
			player->dirZ = true;
			player->groundZCheck = true;
			player->groundCheck = false;


			player->jumpDelay = 0;
			return new PlayerZorderJumpState();
		}
			   		
		player->jumpZ = true;
		player->jumpDelay = 0;
		return new PlayerWalkState();


	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (player->dir == true && player->jumpDelay <= 0.7f && player->jumpZ == true)
		{
			player->dir = true;
			player->jumpZ = false;
			player->dirZ = false;
			player->groundZCheck = true;
			player->groundCheck = false;

			player->jumpDelay = 0;
			return new PlayerZorderJumpState();
		}
		if (player->dir == false && player->jumpDelay <= 0.7f && player->jumpZ == true) 
		{
			player->dir = false;
			player->jumpZ = false;
			player->dirZ = false;
			player->groundZCheck = true;
			player->groundCheck = false;
					   
			player->jumpDelay = 0;
			return new PlayerZorderJumpState();
		}
		
		player->jumpZ = true;
		player->jumpDelay = 0;
		return new PlayerWalkState();

	}

	//점프
	if (KEYMANAGER->isOnceKeyDown('J'))
	{

		return new PlayerJumpState();
	}

	//공격
	//주먹공격
	if (KEYMANAGER->isOnceKeyDown('L'))
	{

		return new PlayerAttackState();

	}

	//발차기
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		if (player->item == nullptr)
		{
			return new PlayerKickAttackState();
		}
		else
		{
			player->isCatch = true;
			player->isPick = true;
			if (player->dir == false)
			{
				player->ChangeClip("two_hand_pick_right", false);
			}
			else
			{
				player->ChangeClip("two_hand_pick_left", false);
			}
		}

	}
	


	//막기
	if (KEYMANAGER->isStayKeyDown('K'))
	{
		player->block = true;
		return new PlayerBlockState();
	
	}
	
	//공격 스킬
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		return new PlayerKickSkillState();
	}


	return nullptr;
}

void PlayerIdleState::Update(Player * player)
{
	if (player->pickDelay > 0.3f && player->isPick == true)
	{
		player->PickItem();
		player->isPick = false;
	}
}

void PlayerIdleState::Enter(Player * player)
{
	if (player->isCatch == true)
	{
		if(player->dir == false)
			player->ChangeClip("two_hand_idle_right", false);
		else
			player->ChangeClip("two_hand_idle_left", false);
	}
	else
	{
		if (player->dir == false)
		{
			player->ChangeClip("idle_right", false);
		}
		else
		{
			player->ChangeClip("idle_left", false);
		}
	}
}

void PlayerIdleState::Exit(Player * player)
{
}
