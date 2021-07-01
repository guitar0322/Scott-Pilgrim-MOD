#pragma once
#include "EnemyState.h"

class JesseDieState : public EnemyState
{
private:

public:
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);
};

