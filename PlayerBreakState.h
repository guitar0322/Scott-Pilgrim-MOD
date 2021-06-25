#pragma once
#include "PlayerState.h"
class PlayerBreakState :
	public PlayerState
{
private:
	float _dashSpeed;		//�޸��� �� �� ���ǵ� ��
public:
	virtual PlayerState* InputHandle(Player* player);
	virtual void Update(Player* player);
	virtual void Enter(Player* player);
	virtual void Exit(Player* player);
};

