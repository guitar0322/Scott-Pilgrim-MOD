/* LUKE ATTACK1 STATE ~.H~ */
#pragma once
#include "EnemyState.h"

class LukeAttack1State : public EnemyState
{
private:

public:
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);
};