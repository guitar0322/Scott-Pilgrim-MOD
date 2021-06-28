#include "stdafx.h"
#include "Matthewattack3state.h"
#include "Matthewidlestate.h"
#include "Matthewattackstate.h"
#include "Matthew.h"

Matthewstate * Matthewattack3state::Update(Matthew * matthew)
{
	_attackTime3 += TIMEMANAGER->getElapsedTime();
	if (_attackTime3 >= 2.0f)
	{
		return new Matthewidlestate;
	}

	return nullptr;
}

void Matthewattack3state::Enter(Matthew * matthew)
{
	_attackTime3 = 0;
	if (matthew->Getdir()==false)
	{
		matthew->ChangeCilp("Matthewattack3Right", true);
	}
	else
	{
		matthew->ChangeCilp("Matthewattack3Left", true);
	}
}

void Matthewattack3state::Exit(Matthew * matthew)
{
}
