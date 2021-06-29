#include "stdafx.h"
#include "Matthewattackstate.h"
#include "Matthewattack2state.h"
#include "Matthewidlestate.h"
#include "Matthew.h"

Matthewstate * MatthewAttackState::Update(Matthew * matthew)
{
	_attackTime += TIMEMANAGER->getElapsedTime();
	if (_attackTime >= 2.0f)
	{
		return new MatthewAttack2State;
	}
	return nullptr;
}

void MatthewAttackState::Enter(Matthew * matthew)
{
	_attackTime = 0;

	if (matthew->Getdir() == false)
	{
		matthew->ChangeCilp("matthew_attack1_right", true);
	}
	else
	{
		matthew->ChangeCilp("matthew_attack1_left", true);
	}
}

void MatthewAttackState::Exit(Matthew * matthew)
{
}
