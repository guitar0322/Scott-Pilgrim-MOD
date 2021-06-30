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
#include "PlayerTwoHandAttackState.h"
#include "Player.h"

PlayerState * PlayerIdleState::InputHandle(Player * player)
{
	//좌우 걷기 모드
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		//두번 눌렀을 때 run 상태로 변경
		if (player->dir == false && player->runDelay <= 0.5f && player->runKeyPress == true)
		{
			player->dir = false;
			player->runKeyPress = false;
			player->isRun = true;

			player->runDelay = 0;
			return new PlayerRunState();
		}
		player->dir = false;
		player->runKeyPress = true;
		player->runDelay = 0;
		player->isRun = false;
		return new PlayerWalkState();
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (player->dir == true && player->runDelay <= 0.5f && player->runKeyPress == true)
		{
			player->dir = true;
			player->runKeyPress = false;
			player->isRun = true;
			player->runDelay = 0;
			return new PlayerRunState();
		}
		player->dir = true;
		player->runKeyPress = true;
		player->isRun = false;
		player->runDelay = 0;
		return new PlayerWalkState();
	}
	//위 아래 걷기 모드
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (player->dirZ == true && player->jumpDelay <= 0.8f && player->jumpZ == true)
		{
			player->dirZ = true; //위방향
			player->jumpZ = false;
			player->jumpDelay = 0;
			return new PlayerZorderJumpState();
		}

		player->dirZ = true;
		player->jumpZ = true;
		player->jumpDelay = 0;
		return new PlayerWalkState();
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (player->dirZ == false && player->jumpDelay <= 0.8f && player->jumpZ == true)
		{
			player->dirZ = false; //아래방향
			player->jumpZ = false;
			player->jumpDelay = 0;
			return new PlayerZorderJumpState();
		}
		player->dirZ = false;
		player->jumpZ = true;
		player->jumpDelay = 0;
		return new PlayerWalkState();
	}

	//점프
	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		player->jumpZ = false;
		return new PlayerJumpState();
	}

	//공격
	//주먹공격
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		player->jumpZ = false;
		if (player->isCatch == false)
		{
			return new PlayerAttackState();
		}
		else
		{
			return new PlayerTwoHandAttackState();
		}
	}

	//발차기
	if (KEYMANAGER->isStayKeyDown('I'))
	{
		player->jumpZ = false;

		if (player->item == nullptr)
		{
			return new PlayerKickAttackState();
		}
		else
		{
			if (player->isCatch == false && player->isCatch == false)
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
			/*
			if (player->isCatch == true && player->isPick == true)
			{
				player->PutItem();
				player->isPick = false;
				if (player->dir == false)
				{
					player->ChangeClip("player_idle_right", false);
				}
				else
				{
					player->ChangeClip("player_idle_left", false);

				}
			}*/
		}

	}
	


	//막기
	if (KEYMANAGER->isStayKeyDown('K'))
	{
		player->jumpZ = false;

		player->block = true;
		return new PlayerBlockState();
	
	}
	
	//공격 스킬
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		player->jumpZ = false;

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
