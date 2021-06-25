#pragma once
#include "EnemyState.h"

class LukeRunState : public EnemyState
{
public:
	virtual EnemyState* Update(Enemy* enemy);
	virtual void Enter(Enemy* enemy);
	virtual void Exit(Enemy* enemy);
};

