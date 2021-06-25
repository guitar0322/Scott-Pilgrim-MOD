#pragma once

class Enemy;

class EnemyState
{
public:
	virtual EnemyState* Update(Enemy* enemy) = 0;
	virtual void Enter(Enemy* enemy) = 0;
	virtual void Exit(Enemy* enemy) = 0;
};

