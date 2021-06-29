#pragma once
#include "EnemyState.h"
class DobermanMoveState :
	public EnemyState
{
private:
	float _delaytime;


public:
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);
};

