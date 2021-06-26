#include "stdafx.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerJumpState.h"
#include "PlayerZorderJumpState.h"
#include "PlayerRunState.h"
#include "PlayerAttackState.h"
#include "PlayerShieldState.h"
#include "PlayerKickAttackState.h"
#include "Player.h"

PlayerState * PlayerIdleState::InputHandle(Player * player)
{
	//좌우 걷기 모드
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		//두번 눌렀을 때 run 상태로 변경
		if (player->dir == false && player->runDelay <= 0.5f && player->dash == true) {
			player->dir = false;
			player->dash = false;

			player->runDelay = 0;
			return new PlayerRunState();
		}
		//플레이어 오른쪽 걷기
		player->dir = false;
		player->dash = true;
		player->runDelay = 0;

		return new PlayerWalkState();
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (player->dir == true && player->runDelay <= 0.5f && player->dash == true) {
			player->dir = true;
			player->dash = false;

			player->runDelay = 0;
			return new PlayerRunState();
		}
		//플레이어 왼쪽
		player->dir = true;
		player->dash = true;
		player->runDelay = 0;


		return new PlayerWalkState();

	}
	//위 아래 걷기 모드
	if (KEYMANAGER->isOnceKeyDown('W'))
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
		player->dash = true;
		player->jumpDelay = 0;
		return new PlayerWalkState();


	}
	if (KEYMANAGER->isOnceKeyDown('S'))
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
		player->dash = true;
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
		return new PlayerKickAttackState();


	}

	//막기
	if (KEYMANAGER->isStayKeyDown('K'))
	{
		player->block = true;
		return new PlayerShieldState();
	
	}
	


	return nullptr;
}

void PlayerIdleState::Update(Player * player)
{

}

void PlayerIdleState::Enter(Player * player)
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

void PlayerIdleState::Exit(Player * player)
{
}
