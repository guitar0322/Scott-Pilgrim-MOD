#pragma once
#include "EnemyState.h"
class WilliamAttackState : public EnemyState
{
private:
	float _attackTime;

public:
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);

};

