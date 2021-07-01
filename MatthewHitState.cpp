#include "stdafx.h"
#include "MatthewHitState.h"
#include "MatthewIdleState.h"
#include "Matthew.h"

Matthewstate * MatthewHitState::Update(Matthew * matthew)
{
	_hitTime = TIMEMANAGER->getElapsedTime();
	if (_hitTime >= 1.0)
	{
		return new MatthewIdleState();
	}

	return nullptr;
}

void MatthewHitState::Enter(Matthew * matthew)
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

void MatthewHitState::Exit(Matthew * matthew)
{
}
