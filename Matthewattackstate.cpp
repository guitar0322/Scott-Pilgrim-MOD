#include "stdafx.h"
#include "Matthewattackstate.h"
#include "Matthewattack2state.h"
#include "Matthewidlestate.h"
#include "Matthew.h"

Matthewstate * Matthewattackstate::Update(Matthew * matthew)
{
	_attackTime += TIMEMANAGER->getElapsedTime();
	if (_attackTime >= 2.0f)
	{
		return new Matthewattack2state;
	}
	return nullptr;
}

void Matthewattackstate::Enter(Matthew * matthew)
{
	_attackTime = 0;

	if (matthew->Getdir() == false)
	{
		matthew->ChangeCilp("Matthewattack1Right", true);
	}
	else
	{
		matthew->ChangeCilp("Matthewattack1Left", true);
	}
}

void Matthewattackstate::Exit(Matthew * matthew)
{
}
