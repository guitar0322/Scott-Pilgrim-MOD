#include "stdafx.h"
#include "PlayerAttackState.h"
#include "PlayerIdleState.h"
#include "Player.h"

PlayerState * PlayerAttackState::InputHandle(Player * player)
{
	//타임매니저로 공격이 마무리되면 idle 스테이트로 변경

	_attackTime += TIMEMANAGER->getElapsedTime();

	if (_attackTime > 0.5f && player->dir == false)
	{
		return new PlayerIdleState();
	}
	if (_attackTime > 0.5f && player->dir == true)
	{
		return new PlayerIdleState();
	}



	return nullptr;
}

void PlayerAttackState::Update(Player * player)
{
	
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		if (_pressL == false && _doubleAttack != true)
		{
			_attackTime = 0;
			_pressL = true;
		}
	
	}

	//최대 프레임이되면 attack2이미지로 
	if (player->animator->currentFrame == (player->animator->curClip->frameNum-1)) {
		if (_pressL == true) {
			if (player->dir == false)
			{
				player->ChangeClip("attack2_right", false);
			}
			else
			{
				player->ChangeClip("attack2_left", false);
			}
			_doubleAttack = true;
			_pressL = false;
		}
	}


}

void PlayerAttackState::Enter(Player * player)
{
	
	if (player->dir == false)
	{
		player->ChangeClip("attack1_right", false);
	}
	else
	{
		player->ChangeClip("attack1_left", false);
	}

}
	

void PlayerAttackState::Exit(Player * player)
{

}
