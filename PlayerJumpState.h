#pragma once
#include "PlayerState.h"
class PlayerJumpState :
	public PlayerState
{

private:
	int _jumpPower;
	int _gravity;
	int _count;


public:
	virtual PlayerState* InputHandle(Player* player);
	virtual void Update(Player * player);
	virtual void Enter(Player * player);
	virtual void Exit(Player * player);


};

