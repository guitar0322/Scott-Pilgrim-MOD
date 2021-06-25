#pragma once
#include "EnemyState.h"

class LukeIdleState : public EnemyState
{
private : 
	float _idelTime;

public:
	virtual EnemyState* Update(Enemy* enemy);
	virtual void Enter(Enemy* enemy);
	virtual void Exit(Enemy* enemy);
};

