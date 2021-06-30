#include "stdafx.h"
#include "MatthehHitState.h"
#include "MatthewIdleState.h"
#include "Matthew.h"

Matthewstate * MatthehHitState::Update(Matthew * matthew)
{
	_hitTime = TIMEMANAGER->getElapsedTime();
	if (_hitTime >= 2.0)
	{
		return new MatthewIdleState();
	}

	return nullptr;
}

void MatthehHitState::Enter(Matthew * matthew)
{
	_hitTime = 0;
	if (matthew->Getdir() == false)
	{
		matthew->ChangeCilp("matthew_hit_right", true);
	}
	else
	{
		matthew->ChangeCilp("matthew_hit_left", true);
	}

}

void MatthehHitState::Exit(Matthew * matthew)
{
}
