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
	//�� �Ʒ� �ȱ� ���
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (player->dirZ == true && player->jumpDelay <= 0.8f && player->jumpZ == true)
		{
			player->jumpZ = false;
			player->dirZ = true;
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
		if (player->dirZ == false && player->jumpZ == true && player->jumpDelay <= 0.8f)
		{
			player->jumpZ = false;
			player->dirZ = false;
			player->jumpDelay = 0;
			return new PlayerZorderJumpState();
		}

		player->dirZ = false;
		player->jumpZ = true;
		player->jumpDelay = 0;
		return new PlayerWalkState();
	}

	//����
	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		_playerJump = true;
		player->jumpZ = false;
		player->hitable = false;
		player->isJump = true;

		return new PlayerJumpState();
	}

	//����
	//�ָ԰���
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		player->jumpZ = false;
		player->pressL = true;

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
					player->ChangeClip("two_hand_pick_right", true);
				}
				else
				{
					player->ChangeClip("two_hand_pick_left", true);
				}
			}
			
			else if (player->isCatch == true)
			{
				player->isPick = false;
				player->isThrow = true;
				if (player->dir == false)
				{
					player->ChangeClip("two_hand_walk_throw_right", true);
					player->equipItem->GetComponent<Item>()->ChangeClip("trashbox_walk_throw_right", false);
				}
				else
				{
					player->ChangeClip("two_hand_walk_throw_left", true);
					player->equipItem->GetComponent<Item>()->ChangeClip("trashbox_walk_throw_left", false);
				}
			}
		}
	}
	//����
	if (KEYMANAGER->isStayKeyDown('K'))
	{
		if (player->isCatch == false)
		{
			player->jumpZ = false;
			player->block = true;
			return new PlayerBlockState();
		}
	}

	//���� ��ų
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		if (player->isCatch == false)
		{
			player->jumpZ = false;
			return new PlayerKickSkillState();
		}
		
	}
	return nullptr;
}

void PlayerIdleState::Update(Player * player)
{
	if (player->isCatch == true && player->isPick == false)
	{
		if (player->dir == false)
		{
			if (player->animator->currentFrame == 0)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() - 15, player->transform->GetY() - 78);
			}
			if (player->animator->currentFrame == 1)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() - 16, player->transform->GetY() - 80);
			}
			if (player->animator->currentFrame == 2)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() - 15, player->transform->GetY() - 79);
			}
			if (player->animator->currentFrame == 3)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() - 15, player->transform->GetY() - 79);
			}

			if (player->isThrow)
			{
				if (player->animator->currentFrame == 0)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() - 50, player->transform->GetY() - 50);
				}
				if (player->animator->currentFrame == 1)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() - 44, player->transform->GetY() - 43);
				}
				if (player->animator->currentFrame == 2)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() - 41, player->transform->GetY() - 40);
				}
			}
		}
		else
		{
			if(player->animator->currentFrame == 0)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 15, player->transform->GetY() - 78);
			}
			if (player->animator->currentFrame == 1)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 15, player->transform->GetY() - 79);
			}
			if (player->animator->currentFrame == 2)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 15, player->transform->GetY() - 79);
			}
			if (player->animator->currentFrame == 3)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 15, player->transform->GetY() - 79);
			}

			if (player->isThrow)			
			{
				if (player->animator->currentFrame == 0)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() + 50, player->transform->GetY() - 50);
				}
				if (player->animator->currentFrame == 1)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() + 44, player->transform->GetY() - 43);
				}
				if (player->animator->currentFrame == 2)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() + 41, player->transform->GetY() - 40);
				}
			}
		}
	}

	
}

void PlayerIdleState::Enter(Player * player)
{
	_playerJump = false;
	player->block = false;
	player->isRun = false;
	if (player->isCatch == true)
	{
		if (player->dir == false)
		{
			player->equipItem->GetComponent<Item>()->ChangeClip("trashbox_right", false);
			player->ChangeClip("two_hand_idle_right", true);
		}
		else
		{
			player->equipItem->GetComponent<Item>()->ChangeClip("trashbox_left", false);
			player->ChangeClip("two_hand_idle_left", true);
		}
	}
	else
	{
		if (player->dir == false)
		{
			player->ChangeClip("idle_right", true);
		}
		else
		{
			player->ChangeClip("idle_left", true);
		}
	}
}

void PlayerIdleState::Exit(Player * player)
{
}
