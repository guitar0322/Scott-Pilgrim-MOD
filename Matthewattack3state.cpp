#include "stdafx.h"
#include "Matthewattack3state.h"
#include "Matthewidlestate.h"
#include "MatthewPalmwindState.h"
#include "Matthew.h"

Matthewstate * MatthewAttack3State::Update(Matthew * matthew)
{
	_attackTime3 += TIMEMANAGER->getElapsedTime();
	if (_attackTime3 >= 3.0f)
	{
		return new MatthewPalmwindState;
	}
	if (_attackTime3 >= 5.0f)
	{
		return new MatthewIdleState;
	}


	return nullptr;
}

void MatthewAttack3State::Enter(Matthew * matthew)
{
	_attackTime3 = 0;
	if (matthew->Getdir()==false)
	{
		matthew->ChangeCilp("matthew_attack3_right", true);
	}
	else
	{
		matthew->ChangeCilp("matthew_attack3_left", true);
	}
}

void MatthewAttack3State::Exit(Matthew * matthew)
{
}
