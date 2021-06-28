#include "stdafx.h"
#include "Matthewmovestate.h"
#include "Matthewidlestate.h"
#include "Matthewattackstate.h"
#include "Matthew.h"

Matthewstate * Matthewmovestate::Update(Matthew * matthew)
{
	if (matthew->transform->GetX() < matthew->GetPlayer()->GetX())
	{
		if (matthew->Getdir() == true)
		{
			matthew->ChangeCilp("MatthewmoveRight", false);
			matthew->Setdir(false);
		}
	}
	else
	{
		if (matthew->Getdir() == false)
		{
			matthew->ChangeCilp("MatthewmoveLeft", false);
			matthew->Setdir(true);
		}
	}
	if (GetDistance(matthew->transform->GetX(), matthew->transform->GetY(),
		matthew->GetPlayer()->GetX(), matthew->GetPlayer()->GetY()) > 200)
	{
		return new Matthewidlestate;
	}
	if (GetDistance(matthew->transform->GetX(),matthew->transform->GetY(),matthew->GetPlayer()->GetX(),matthew->GetPlayer()->GetY())<50)
	{
		return new Matthewattackstate;
	}

	float Angle = GetAngle(matthew->transform->GetX(), matthew->transform->GetY(), matthew->GetPlayer()->GetX(), matthew->GetPlayer()->GetY());
	matthew->transform->Move(matthew->GetSpeed()*TIMEMANAGER->getElapsedTime()*cosf(Angle),
							 matthew->GetSpeed()*TIMEMANAGER->getElapsedTime()*-sinf(Angle));

	return nullptr;
}

void Matthewmovestate::Enter(Matthew * matthew)
{
	if (matthew->Getdir() == false)
	{
		matthew->ChangeCilp("MatthewmoveRight", true);
	}
	else
	{
		matthew->ChangeCilp("MatthewmoveLeft", true);
	}

}

void Matthewmovestate::Exit(Matthew * matthew)
{
}
