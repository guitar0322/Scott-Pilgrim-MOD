#pragma once
#include "EnemyState.h"

class JesseIdleState : public EnemyState
{
private:
	float _idleTime;
	float _idleMaxTime;

public:
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);
};

