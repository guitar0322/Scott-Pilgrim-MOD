#pragma once
#include "PlayerState.h"

class PlayerZorderJumpState :
	public PlayerState
{
private:
	float _jumpPowerZorder;
	float _speedZ;

public:
	virtual PlayerState* InputHandle(Player* player);
	virtual void Update(Player* player);
	virtual void Enter(Player* player);
	virtual void Exit(Player* player);



};

