#include "stdafx.h"
#include "Dobermanidlestate.h"
#include "Dobermanmovestate.h"
#include "Doberman.h"

Dobermanstate* Dobermanidlestate::Update(Doberman * doberman)
{
	/*int SaveTimer;*/


	if (GetDistance(doberman->transform->GetX(),doberman->transform->GetY(),
		doberman->GetPlayer()->GetX(),doberman->GetPlayer()->GetY()) < 300)
	{
		if (doberman->transform->GetX() < doberman->GetPlayer()->GetX())
		{
			if (doberman->GetDir() == true)
			{
				doberman->ChangeClip("idleRight",true);
				doberman->SetDir(false);
			}
			return new Dobermanmovestate();
		}
		else
		{
			if (doberman->GetDir()==false)
			{
				doberman->ChangeClip("idleLeft",true);
				doberman->SetDir(true);
			}
			return new Dobermanmovestate();
		}
	}
	//if (TIMEMANAGER->getWorldTime() >= SaveTimer + 5)
	//{
	//	switch (RND->getInt(3))
	//	{
	//	case 0:
	//		doberman->transform->Move(doberman->GetSpeed()*TIMEMANAGER->getElapsedTime()*cosf(Angle),
	//			doberman->GetSpeed()*TIMEMANAGER->getElapsedTime()*-sinf(Angle));

	//	case 1:

	//	case 2:

	//	default:
	//		break;
	//	}
	//}



	return nullptr;
}

void Dobermanidlestate::Enter(Doberman * doberman)
{
	if (doberman->GetDir() == false)
	{
		doberman->ChangeClip("idleRight", true);
	}
	else
	{
		doberman->ChangeClip("idleLeft", true);
	}
}

void Dobermanidlestate::Exit(Doberman * doberman)
{
}
