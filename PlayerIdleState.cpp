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
	//�¿� �ȱ� ���
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (player->dir == false && player->runDelay <= 0.5f && player->dash == true) {
			player->dir = false;
			player->dash = false;
			player->dashStop = false;

			player->runDelay = 0;
			return new PlayerRunState();
		}
		//�÷��̾� ������
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
			player->dashStop = false;

			player->runDelay = 0;
			return new PlayerRunState();
		}
		//�÷��̾� ����
		player->dir = true;
		player->dash = true;
		player->runDelay = 0;


		return new PlayerWalkState();

	}
	//�� �Ʒ� �ȱ� ���
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (player->dir == true && player->jumpDelay <= 0.5f && player->jumpZ == true)
		{
			player->dir = true;
			player->jumpZ = false;
			player->dirZ = true;

			player->jumpDelay = 0;
			return new PlayerZorderJumpState();
		}
		if (player->dir == false && player->jumpDelay <= 0.5f && player->jumpZ == true)
		{
			player->dir = false;
			player->jumpZ = false;
			player->dirZ = true;

			player->jumpDelay = 0;
			return new PlayerZorderJumpState();
		}
			   		
		player->jumpZ = true;
		player->dashStop = false;
		player->dash = true;
		player->jumpDelay = 0;
		return new PlayerWalkState();


	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (player->dir == true && player->jumpDelay <= 0.5f && player->jumpZ == true)
		{
			player->dir = true;
			player->jumpZ = false;
			player->dirZ = false;


			player->jumpDelay = 0;
			return new PlayerZorderJumpState();
		}
		if (player->dir == false && player->jumpDelay <= 0.5f && player->jumpZ == true) {
			player->dir = false;
			player->jumpZ = false;
			player->dirZ = false;


			player->jumpDelay = 0;
			return new PlayerZorderJumpState();
		}
		
		player->dirZ = false;
		player->jumpZ = true;
		player->dashStop = false;
		player->dash = true;
		player->jumpDelay = 0;
		return new PlayerWalkState();

	}

	//����
	if (KEYMANAGER->isOnceKeyDown('J'))
	{

		return new PlayerJumpState();
	}

	//����
	//�ָ԰���
	if (KEYMANAGER->isOnceKeyDown('L'))
	{

		player->attackChange = true; //2������
		return new PlayerAttackState();


	}
	//������
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		player->dashStop = false;
		return new PlayerKickAttackState();


	}

	//����
	if (KEYMANAGER->isStayKeyDown('K'))
	{
		player->dashStop = false;
		player->shield = true;
		return new PlayerShieldState();
	
	}
	


	return nullptr;
}

void PlayerIdleState::Update(Player * player)
{

	_dashSpeed -= player->GetFriction() * TIMEMANAGER->getElapsedTime();

	if (player->dashStop == true)
	{
		if (player->dir == false)
		{
			player->transform->MoveX(_dashSpeed * TIMEMANAGER->getElapsedTime());
			player->ground->MoveX(_dashSpeed * TIMEMANAGER->getElapsedTime());


		}
		else
		{
			player->transform->MoveX(-_dashSpeed * TIMEMANAGER->getElapsedTime());
			player->ground->MoveX(-_dashSpeed * TIMEMANAGER->getElapsedTime());
		}

		if (_dashSpeed < 0)
		{

			player->dashStop = false;
		}
	}



}

void PlayerIdleState::Enter(Player * player)
{
	_dashSpeed = 80;


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
