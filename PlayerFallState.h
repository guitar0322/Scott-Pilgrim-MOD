#pragma once
#include "PlayerState.h"
class PlayerFallState :
	public PlayerState
{
private:

public:
	virtual PlayerState* InputHandle(Player* player);
	virtual void Update(Player * player);
	virtual void Enter(Player * player);
	virtual void Exit(Player * player);
};

