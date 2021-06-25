#pragma once
#include "EnemyState.h"

class LukeAttackState : public EnemyState
{
private:
	float _attackTime;
public:
	virtual EnemyState* Update(Enemy* enemy);
	virtual void Enter(Enemy* enemy);
	virtual void Exit(Enemy* enemy);
};

