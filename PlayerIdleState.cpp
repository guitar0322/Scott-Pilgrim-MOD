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
	//�¿� �ȱ� ���
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		//�ι� ������ �� run ���·� ����
		
		if (player->isCatch == true) //�μչ��� �������
		{
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
		else
		{
			if (player->dir == false && player->runDelay <= 0.5f && player->runKeyPress == true)
			{
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

			
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (player->isCatch == true) //�μչ��� �������
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
			player->runDelay = 0;
			player->isRun = false;

			return new PlayerWalkState();
		}
		else
		{
			if (player->dir == true && player->runDelay <= 0.5f && player->runKeyPress == true) 
			{
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




	}
	//�� �Ʒ� �ȱ� ���
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		//�μ�
		if (player->isCatch == true)  //�μ����� ����� ��
		{
			if (player->dirZ == true && player->dir == true 
					&& player->jumpDelay <= 0.8f && player->jumpZ == true)
			{
				player->dir = true;
				player->jumpZ = false;
				player->dirZ = true;
				player->groundZCheck = true;
				player->groundCheck = false;

				player->jumpDelay = 0;
				return new PlayerZorderJumpState();
			}
			else if (player->dirZ == true && player->dir == false 
						&& player->jumpDelay <= 0.8f && player->jumpZ == true)
			{
				player->dir = false;
				player->jumpZ = false;
				player->dirZ = true;
				player->groundZCheck = true;
				player->groundCheck = false;

				player->jumpDelay = 0;
				return new PlayerZorderJumpState();

			}

			player->dirZ = true;
			player->jumpZ = true;
			player->jumpDelay = 0;
			return new PlayerWalkState();
		}
		else //�μ����� �� ����� ��
		{
			if (player->dirZ == true && player->dir == true 
					&& player->jumpDelay <= 0.8f && player->jumpZ == true)
			{
				player->dir = true;
				player->jumpZ = false;
				player->dirZ = true;
				player->groundZCheck = true;
				player->groundCheck = false;

				player->jumpDelay = 0;
				return new PlayerZorderJumpState();
			}
			else if (player->dirZ == true && player->dir == false 
				&& player->jumpDelay <= 0.8f && player->jumpZ == true)
			{
				player->dir = false;
				player->jumpZ = false;
				player->dirZ = true;
				player->groundZCheck = true;
				player->groundCheck = false;

				player->jumpDelay = 0;
				return new PlayerZorderJumpState();

			}

			player->dirZ = true;
			player->jumpZ = true;
			player->jumpDelay = 0;
			return new PlayerWalkState();
		}

	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (player->isCatch == true) //�μ����� ����� ��
		{
			if (player->dirZ == false && player->dir == true 
					&& player->jumpDelay <= 0.8f && player->jumpZ == true)
			{
				player->dir = true;
				player->jumpZ = false;
				player->dirZ = false;
				player->groundZCheck = true;
				player->groundCheck = false;

				player->jumpDelay = 0;
				return new PlayerZorderJumpState();
			}
			else if (player->dirZ == false && player->dir == false 
						&& player->jumpDelay <= 0.8f && player->jumpZ == true)
			{
				player->dir = false;
				player->jumpZ = false;
				player->dirZ = false;
				player->groundZCheck = true;
				player->groundCheck = false;

				player->jumpDelay = 0;
				return new PlayerZorderJumpState();
			}

			player->dirZ = false;
			player->jumpZ = true;
			player->jumpDelay = 0;
			return new PlayerWalkState();
		}
		else //�μ����� �� ����� ��
		{
			if (player->dirZ == false && player->dir == true 
					&& player->jumpDelay <= 0.8f && player->jumpZ == true)
			{
				player->dir = true;
				player->jumpZ = false;
				player->dirZ = false;
				player->groundZCheck = true;
				player->groundCheck = false;

				player->jumpDelay = 0;
				return new PlayerZorderJumpState();
			}
			else if (player->dirZ == false && player->dir == false 
						&& player->jumpDelay <= 0.8f && player->jumpZ == true)
			{
				player->dir = false;
				player->jumpZ = false;
				player->dirZ = false;
				player->groundZCheck = true;
				player->groundCheck = false;

				player->jumpDelay = 0;
				return new PlayerZorderJumpState();
			}

			player->dirZ = false;
			player->jumpZ = true;
			player->jumpDelay = 0;
			return new PlayerWalkState();
		}

	}

	//����
	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		player->jumpZ = false;

		return new PlayerJumpState();
		
	}

	//����
	//�ָ԰���
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

	//������
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		player->jumpZ = false;

		if (player->item == nullptr)
		{
			return new PlayerKickAttackState();
		}
		else
		{
			if (player->isCatch == false && player->isPick == false)
			{
				player->isCatch = true;
				player->isPick = true;
				player->PickItem();
				if (player->dir == false)
				{
					player->ChangeClip("two_hand_pick_right", false);
				}
				else
				{
					player->ChangeClip("two_hand_pick_left", false);
				}
			}
			
			else if (player->isCatch == true)
			{
				player->PutItem();
				player->isPick = false;
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

	}
	


	//����
	if (KEYMANAGER->isStayKeyDown('K'))
	{
		player->jumpZ = false;

		player->block = true;
		return new PlayerBlockState();
	
	}
	
	//���� ��ų
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

	if (player->isCatch == true)
	{
		_itemShakeTime += TIMEMANAGER->getElapsedTime();
		if (_itemShakeTime >= 0.5 && player->isCatch == true)
		{
			if (_itemShakeDir == false)
				player->GetItemTransform()->MoveY(-1);
			else
				player->GetItemTransform()->MoveY(1);

			_itemShakeDir = !_itemShakeDir;
			_itemShakeTime = 0;
		}
	}
}

void PlayerIdleState::Enter(Player * player)
{
	_itemShakeTime = 0;
	if (player->isCatch == true)
	{
		player->equipItem->GetComponent<Item>()->ChangeClip("trashbox", false);
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
	if (_itemShakeDir == true && player->isCatch == true)
	{
		player->GetItemTransform()->MoveY(-1);
	}
}
