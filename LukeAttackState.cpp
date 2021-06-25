#include "stdafx.h"
#include "Enemy.h"
#include "LukeIdleState.h"
#include "LukeAttackState.h"


EnemyState* LukeAttackState::Update(Enemy* enemy)
{
	_attackTime += TIMEMANAGER->getElapsedTime();
	if (_attackTime >= 1.0f)
		return new LukeIdleState();

	return nullptr;
}

void LukeAttackState::Enter(Enemy* enemy)
{
	_attackTime = 0;
	if (enemy->GetDir() == false)
		enemy->ChangeClip("luke_attackRight", true);
	else
		enemy->ChangeClip("luke_attackLeft", true);
}

void LukeAttackState::Exit(Enemy* enemy)
{
}
