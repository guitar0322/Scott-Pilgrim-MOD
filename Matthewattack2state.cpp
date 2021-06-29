#include "stdafx.h"
#include "Matthewattack2state.h"
#include "Matthewattack3state.h"
#include "Matthewidlestate.h"
#include "Matthew.h"

Matthewstate * MatthewAttack2State::Update(Matthew * matthew)
{
	_attackTime2 += TIMEMANAGER->getElapsedTime();
	if (_attackTime2 >= 2.0f)
	{
		return new MatthewAttack3State;
	}

	return nullptr;
}

void MatthewAttack2State::Enter(Matthew * matthew)
{
	_attackTime2 = 0;
	if (matthew->Getdir() == false)
	{
		matthew->ChangeCilp("matthew_attack2_right", true);
	}
	else
	{
		matthew->ChangeCilp("matthew_attack2_left", true);
	}
}

void MatthewAttack2State::Exit(Matthew * matthew)
{
}
