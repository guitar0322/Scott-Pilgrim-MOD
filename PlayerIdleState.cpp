#include "stdafx.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerJumpState.h"
#include "PlayerRunState.h"
#include "PlayerAttackState.h"
#include "Player.h"

PlayerState * PlayerIdleState::InputHandle(Player * player)
{
	//�¿� �ȱ� ���
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (player->dir == false && player->runDelay <= 0.5f && player->dash == true) {
			player->dir = false;
			player->dash = false;
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
		//�÷��̾� ������
		player->dirZ = false; //Z�� ��

		player->dash = true;
		return new PlayerWalkState();


	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		//�÷��̾� ����
		player->dirZ = true; //Z�� ��

		player->dash = true;

		return new PlayerWalkState();

	}

	//����
	if (KEYMANAGER->isOnceKeyDown('J'))
	{

		return new PlayerJumpState();
	}

	//����

	if (KEYMANAGER->isOnceKeyDown('L'))
	{

		player->attackChange = true; //2������
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
