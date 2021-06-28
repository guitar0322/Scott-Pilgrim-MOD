#include "stdafx.h"
#include "Matthewidlestate.h"
#include "Matthewmovestate.h"
#include "Matthew.h"

Matthewstate * Matthewidlestate::Update(Matthew* matthew)
{
	if (GetDistance(matthew->transform->GetX(), matthew->transform->GetY(),
		matthew->GetPlayer()->GetX(), matthew->GetPlayer()->GetY()) < 200)
	{
		if (matthew->transform->GetX() < matthew->GetPlayer()->GetX())
		{
			if (matthew->Getdir() == true)
			{
				matthew->ChangeCilp("MatthewidleRight", true);
				matthew->Setdir(false);
			}
			return new Matthewmovestate();
		}
		else
		{
			if (matthew->Getdir() == false)
			{
				matthew->ChangeCilp("MatthewidleLeft", true);
				matthew->Setdir(true);
			}
			return new Matthewmovestate();
		}
	}
	return nullptr;
}

void Matthewidlestate::Enter(Matthew * matthew)
{
	if (matthew->Getdir()==false)
	{
		matthew->ChangeCilp("MatthewidleRight", true);
	}
	else
	{
		matthew->ChangeCilp("MatthewidleLeft", true);
	}

}

void Matthewidlestate::Exit(Matthew * matthew)
{
}
