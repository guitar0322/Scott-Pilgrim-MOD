#include "stdafx.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerJumpState.h"
#include "PlayerRunState.h"
#include "PlayerAttackState.h"
#include "Player.h"

PlayerState * PlayerIdleState::InputHandle(Player * player)
{
	//좌우 걷기 모드
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (player->dir == false && player->runDelay <= 0.5f && player->dash == true) {
			player->dir = false;
			player->dash = false;
			player->runDelay = 0;
			return new PlayerRunState();
		}
		//플레이어 오른쪽
		player->dir = false;
		player->dash = true;
		player->runDelay = 0;

		return new PlayerWalkState();


	}
	if (KEYMANAGER->isStayKeyDown('A'))
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
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		//플레이어 오른쪽
		player->dirZ = false; //Z축 위

		player->dash = true;
		return new PlayerWalkState();


	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		//플레이어 왼쪽
		player->dirZ = true; //Z축 위

		player->dash = true;

		return new PlayerWalkState();

	}

	//점프
	if (KEYMANAGER->isOnceKeyDown('J'))
	{

		return new PlayerJumpState();
	}

	//공격

	if (KEYMANAGER->isOnceKeyDown('L'))
	{

		player->attackChange = true; //2번공격
		return new PlayerAttackState();


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
