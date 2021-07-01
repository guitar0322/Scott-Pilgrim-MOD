#include "stdafx.h"
#include "MatthewPalmwindState.h"
#include "Matthewidlestate.h"
#include "MatthewHitState.h"
#include "MatthewBlockState.h"
#include "MatthewPhaseReadyState.h"
#include "Matthew.h"

Matthewstate * MatthewPalmwindState::Update(Matthew * matthew)
{
	if (matthew->animator->GetEnd() == true)
	{
		if (matthew->Getdir() == false)
		{
			matthew->transform->Move(-90, 40);
		}
		else
		{
			matthew->transform->Move(90, 40);
		}
		return new MatthewPhaseReadyState();
	}
	return nullptr;
}

void MatthewPalmwindState::Enter(Matthew * matthew)
{
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
