#pragma once
#include "EnemyState.h"
class MalcolmhitState :
	public EnemyState
{
private:
	float _hittime;

public:
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);

};

