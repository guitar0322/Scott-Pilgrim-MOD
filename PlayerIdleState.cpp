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
	//�¿� �ȱ� ���
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		//�ι� ������ �� run ���·� ����
		if (player->dir == false && player->runDelay <= 0.5f && player->runKeyPress == true) {
			player->dir = false;
			player->runKeyPress = false;
			player->isRun = true;

			player->runDelay = 0;
			return new PlayerRunState();
		}
		//�÷��̾� ������ �ȱ�
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
		//�÷��̾� ����
		player->dir = true;
		player->runKeyPress = true;
		player->runDelay = 0;
		player->isRun = false;


		return new PlayerWalkState();

	}
	//�� �Ʒ� �ȱ� ���
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

	//����
	if (KEYMANAGER->isOnceKeyDown('J'))
	{

		return new PlayerJumpState();
	}

	//����
	//�ָ԰���
	if (KEYMANAGER->isOnceKeyDown('L'))
	{

		return new PlayerAttackState();

	}

	//������
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		return new PlayerKickAttackState();


	}

	//����
	if (KEYMANAGER->isStayKeyDown('K'))
	{
		player->block = true;
		return new PlayerBlockState();
	
	}
	
	//���� ��ų
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		return new PlayerKickSkillState();
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
