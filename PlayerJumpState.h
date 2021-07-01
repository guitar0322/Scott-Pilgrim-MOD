#pragma once
#include "PlayerState.h"
class PlayerJumpState :
	public PlayerState
{

private:
	int _gravity;		//�÷��̾� �߷°�
	float _speedX;
public:
	virtual PlayerState* InputHandle(Player* player);
	virtual void Update(Player * player);
	virtual void Enter(Player * player);
	virtual void Exit(Player * player);
};

