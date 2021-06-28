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
		/*
		if (player->dir == false && player->isCatch == true)
		{
			player->dir = false;



		}
		*/
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
