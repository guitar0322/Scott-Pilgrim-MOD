#include "stdafx.h"
#include "MatthewPhaseStartState.h"
#include "Matthew.h"
#include "MatthewPhaseSpotlightState.h"

Matthewstate * MatthewPhaseStartState::Update(Matthew * matthew)
{
	_startTime += TIMEMANAGER->getElapsedTime();
	if (_startTime >=0.5f)
	{
		return new MatthewPhaseSpotlightState();
	}
	return nullptr;
}

void MatthewPhaseStartState::Enter(Matthew * matthew)
{
	_startTime = 0;
	if (matthew->Getdir() == false)
	{
		matthew->ChangeCilp("matthew_phase_start_right", false);
	}
	else
	{
		matthew->ChangeCilp("matthew_phase_start_left", false);
	}
}

void MatthewPhaseStartState::Exit(Matthew * matthew)
{
}
