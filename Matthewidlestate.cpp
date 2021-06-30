#include "stdafx.h"
#include "MatthewIdleState.h"
#include "MatthewMoveState.h"
#include "Matthew.h"

Matthewstate * MatthewIdleState::Update(Matthew* matthew)
{
	if (GetDistance(matthew->transform->GetX(), matthew->transform->GetY(),
		matthew->GetPlayer()->GetX(), matthew->GetPlayer()->GetY()) < 200)
	{
		if (matthew->transform->GetX() < matthew->GetPlayer()->GetX())
		{
			if (matthew->Getdir() == true)
			{
				matthew->ChangeCilp("matthew_idle_right", true);
				matthew->Setdir(false);
			}
			return new MatthewMoveState();
		}
		else
		{
			if (matthew->Getdir() == false)
			{
				matthew->ChangeCilp("matthew_idle_left", true);
				matthew->Setdir(true);
			}
			return new MatthewMoveState();
		}
	}
	return nullptr;
}

void MatthewIdleState::Enter(Matthew * matthew)
{
	if (matthew->Getdir()==false)
	{
		matthew->ChangeCilp("matthew_idle_right", true);
	}
	else
	{
		matthew->ChangeCilp("matthew_idle_left", true);
	}

}

void MatthewIdleState::Exit(Matthew * matthew)
{
}
