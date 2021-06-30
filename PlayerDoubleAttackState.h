#pragma once
#include "PlayerState.h"
class PlayerDoubleAttackState :
	public PlayerState
{
private:
	float _speedY;


public:
	virtual PlayerState* InputHandle(Player* player);
	virtual void Update(Player* player);
	virtual void Enter(Player* player);
	virtual void Exit(Player* player);
};

