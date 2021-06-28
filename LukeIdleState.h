#pragma once
#include "EnemyState.h"

class LukeIdleState : public EnemyState
{
private:
	float _idelTime;

public:
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);
};

