#include "stdafx.h"
#include "MatthewAttack2State.h"
#include "MatthewAttack3State.h"
#include "MatthewIdleState.h"
#include "Matthew.h"

Matthewstate * MatthewAttack2State::Update(Matthew * matthew)
{
	_attackTime2 += TIMEMANAGER->getElapsedTime();
	if (_attackTime2 >= 1.0f)
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
