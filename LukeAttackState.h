#pragma once
#include "EnemyState.h"

class LukeAttackState : public EnemyState
{
private:
	float _attackTime;

public:
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);
};