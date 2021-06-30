#include "stdafx.h"
#include "MatthewMoveState.h"
#include "MatthewIdleState.h"
#include "MatthewAttackState.h"
#include "Matthew.h"

Matthewstate * MatthewMoveState::Update(Matthew * matthew)
{
	if (matthew->transform->GetX() < matthew->GetPlayer()->GetX())
	{
		if (matthew->Getdir() == true)
		{
			matthew->ChangeCilp("matthew_move_right", false);
			matthew->Setdir(false);
		}
	}
	else
	{
		if (matthew->Getdir() == false)
		{
			matthew->ChangeCilp("matthew_move_left", false);
			matthew->Setdir(true);
		}
	}
	if (GetDistance(matthew->transform->GetX(), matthew->transform->GetY(),
		matthew->GetPlayer()->GetX(), matthew->GetPlayer()->GetY()) > 200)
	{
		return new MatthewIdleState;
	}
	if (GetDistance(matthew->transform->GetX(),matthew->transform->GetY(),matthew->GetPlayer()->GetX(),matthew->GetPlayer()->GetY())<50)
	{
		return new MatthewAttackState;
	}

	float angle = GetAngle(matthew->transform->GetX(), matthew->transform->GetY(), matthew->GetPlayer()->GetX(), matthew->GetPlayer()->GetY());
	matthew->transform->Move(matthew->GetSpeed()*TIMEMANAGER->getElapsedTime()*cosf(angle),
							 matthew->GetSpeed()*TIMEMANAGER->getElapsedTime()*-sinf(angle));

	return nullptr;
}

void MatthewMoveState::Enter(Matthew * matthew)
{
	if (matthew->Getdir() == false)
	{
		matthew->ChangeCilp("matthew_move_right", true);
	}
	else
	{
		matthew->ChangeCilp("matthew_move_left", true);
	}

}

void MatthewMoveState::Exit(Matthew * matthew)
{
}
