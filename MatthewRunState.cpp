#include "stdafx.h"
#include "MatthewRunState.h"
#include "Matthew.h"
#include "MatthewAttackState.h"
#include "MatthewMoveState.h"

Matthewstate * MatthewRunState::Update(Matthew * matthew)
{
	if (matthew->transform->GetX() < matthew->GetPlayer()->GetX())
	{
		if (matthew->Getdir()==true)
		{
			matthew->ChangeCilp("matthew_run_right", false);
			matthew->Setdir(false);
		}
	}
	else
	{
		if (matthew->Getdir()==false)
		{
			matthew->ChangeCilp("matthew_run_left", false);
			matthew->Setdir(true);
		}
	}
	if (GetDistance(matthew->transform->GetX(), matthew->transform->GetY(),
		matthew->GetPlayer()->GetX(), matthew->GetPlayer()->GetY()) > 300)
	{
		return new MatthewMoveState;
	}


	if (GetDistance(matthew->transform->GetX(), matthew->transform->GetY(), matthew->GetPlayer()->GetX(), matthew->GetPlayer()->GetY()) < 50)
	{
		return new MatthewAttackState;
	}
	float angle = GetAngle(matthew->transform->GetX(), matthew->transform->GetY(),
		matthew->GetPlayer()->GetX(), matthew->GetPlayer()->GetY());
	matthew->transform->Move((matthew->GetSpeed() * 2)*TIMEMANAGER->getElapsedTime()*cosf(angle),
		(matthew->GetSpeed() * 2)*TIMEMANAGER->getElapsedTime()*-sinf(angle));


	return nullptr;
}

void MatthewRunState::Enter(Matthew * matthew)
{
	if (matthew->Getdir()==false)
	{
		matthew->ChangeCilp("matthew_run_right", true);
	}
	else
	{
		matthew->ChangeCilp("matthew_run_left", true);
	}
}

void MatthewRunState::Exit(Matthew * matthew)
{
}
