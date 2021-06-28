#include "stdafx.h"
#include "Matthewattack2state.h"
#include "Matthewattack3state.h"
#include "Matthewidlestate.h"
#include "Matthew.h"

Matthewstate * Matthewattack2state::Update(Matthew * matthew)
{
	_attackTime2 += TIMEMANAGER->getElapsedTime();
	if (_attackTime2 >= 2.0f)
	{
		return new Matthewattack3state;
	}

	return nullptr;
}

void Matthewattack2state::Enter(Matthew * matthew)
{
	_attackTime2 = 0;
	if (matthew->Getdir() == false)
	{
		matthew->ChangeCilp("Matthewattack2Right", true);
	}
	else
	{
		matthew->ChangeCilp("Matthewattack2Left", true);
	}
}

void Matthewattack2state::Exit(Matthew * matthew)
{
}
