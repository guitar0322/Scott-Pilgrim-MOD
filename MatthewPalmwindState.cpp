#include "stdafx.h"
#include "MatthewPalmwindState.h"
#include "Matthewidlestate.h"
#include "Matthewattack3state.h"
#include "MatthehHitState.h"
#include "Matthew.h"

Matthewstate * MatthewPalmwindState::Update(Matthew * matthew)
{
	_palmwindtime += TIMEMANAGER->getElapsedTime();
	if (_palmwindtime >= 2.0f)
	{
		if (matthew->Getdir() == false)
		{
			matthew->transform->Move(-90, 40);
		}
		else
		{
			matthew->transform->Move(90, 40);
		}
		return new MatthewIdleState();
	}
	return nullptr;
}

void MatthewPalmwindState::Enter(Matthew * matthew)
{
	_palmwindtime = 0;
	if (matthew->Getdir() == false)
	{
		matthew->transform->Move(90, -40);
		matthew->ChangeCilp("matthew_palmwind_right", true);
	}
	else
	{
		matthew->transform->Move(-90, -40);
		matthew->ChangeCilp("matthew_palmwind_left", true);
	}



}

void MatthewPalmwindState::Exit(Matthew * matthew)
{
}
