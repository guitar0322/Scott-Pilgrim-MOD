#include "stdafx.h"
#include "PlayerFallState.h"
#include "PlayerGroundState.h"
#include "PlayerJumpKickState.h"
#include "Player.h"

PlayerState * PlayerFallState::InputHandle(Player * player)
{
	int intersectHeight = GROUNDMANAGER->CheckGround(player->collider->rc, player->zOrder->GetZ());
	if (intersectHeight != 0)
	{
		player->transform->MoveY(-intersectHeight);
		player->onGround = true;
		return new PlayerGroundState();
	}

	if (player->transform->GetY() + 52 >= player->zOrder->GetZ()) {
		return new PlayerGroundState();
	}

	
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		return new PlayerJumpKickState();

	}
	return nullptr;
}

void PlayerFallState::Update(Player * player)
{
	//중력값을 올려서 좀 더 빨리 떨어지는 효과를 보여줌
	player->jumpPower += player->GetGravity()*TIMEMANAGER->getElapsedTime();

	player->transform->MoveY(player->jumpPower * TIMEMANAGER->getElapsedTime());

	if (player->isRun == true) //뛸 때 -> 점프
	{
		if (player->dir == false)
		{
			player->transform->MoveX(player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime());
			if (MAPMANAGER->IsInSlope1(player->gameObject) == true) {
				player->zOrder->MoveZ(player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
				MainCam->transform->MoveY(player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
			}
		}
		else
		{
			player->transform->MoveX(-player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime());
			if (MAPMANAGER->IsInSlope1(player->gameObject) == true) {
				player->zOrder->MoveZ(player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
				MainCam->transform->MoveY(player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (player->isRun == true) //뛸 때 -> 점프
		{
			if (player->dir == false)
			{
				player->transform->MoveX(player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime());
				if (MAPMANAGER->IsInSlope1(player->gameObject) == true) {
					player->zOrder->MoveZ(player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
					MainCam->transform->MoveY(player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
				}
			}
			else
			{
				player->transform->MoveX(-player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime());
				if (MAPMANAGER->IsInSlope1(player->gameObject) == true) {
					player->zOrder->MoveZ(player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
					MainCam->transform->MoveY(player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
				}
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (player->isRun == true)
		{
			player->transform->MoveX(-player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime());
			if (MAPMANAGER->IsInSlope1(player->gameObject) == true) {
				player->zOrder->MoveZ(-player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
				MainCam->transform->MoveY(-player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
			}
		}
		else
		{
			player->transform->MoveX(-player->GetSpeed()*TIMEMANAGER->getElapsedTime());
			if (MAPMANAGER->IsInSlope1(player->gameObject) == true) {
				player->zOrder->MoveZ(-player->GetSpeed() * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
				MainCam->transform->MoveY(-player->GetSpeed() * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->zOrder->MoveZ(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->zOrder->MoveZ(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (player->isCatch == true)
		{
			player->dir = false;
			player->ChangeClip("two_hand_fall_right", true);

		}
		else
		{
			player->dir = false;
			player->ChangeClip("fall_right", false);

		}
	
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (player->isCatch == true)
		{
			player->dir = true;
			player->ChangeClip("two_hand_fall_left", true);

		}
		else
		{
			player->dir = true;
			player->ChangeClip("fall_left", false);

		}
	
	}

}

void PlayerFallState::Enter(Player * player)
{
	player->jumpPower = 0;
	if (player->isCatch == true)
	{
		if (player->dir == false)
		{
			player->ChangeClip("two_hand_fall_right", true);
		}
		else
		{
			player->ChangeClip("two_hand_fall_left", true);
		}
	}
	else
	{
		if (player->dir == false)
		{
			player->ChangeClip("fall_right", true);
		}
		else
		{
			player->ChangeClip("fall_left", true);
		}
	}
}

void PlayerFallState::Exit(Player * player)
{
	
}
