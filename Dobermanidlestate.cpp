#include "stdafx.h"
#include "Dobermanidlestate.h"
#include "Doberman.h"

Dobermanstate * Dobermanidlestate::Update(Doberman * doberman)
{
	if (GetDistance(doberman->transform->GetX(),doberman->transform->GetY(),
		doberman->getPlayer()->GetX(),doberman->getPlayer()->GetY()) < 300)
	{
		if (doberman->transform->GetX() < doberman->getPlayer()->GetX())
		{
			if (doberman->getDir() == true)
			{
				doberman->changeClip("idleLeft", true);
				doberman->setDir(false);
			}
		}
		else
		{
			if (doberman->getDir()==false)
			{
				doberman->changeClip("idleLeft",true);
				doberman->setDir(true);
			}
		}
	}
	return nullptr;
}

void Dobermanidlestate::Enter(Doberman * doberman)
{
	if (doberman->getDir() == false)
	{
		doberman->changeClip("idleRight", true);
	}
	else
	{
		doberman->changeClip("idleLeft", true);
	}
}

void Dobermanidlestate::Exit(Doberman * doberman)
{
}
