#pragma once
#include "PlayerState.h"
class PlayerAttackState :
	public PlayerState
{

private:
	int _count;
	int _attackCount;


public:
	virtual PlayerState* InputHandle(Player* player);
	virtual void Update(Player * player);
	virtual void Enter(Player * player);
	virtual void Exit(Player * player);





};

