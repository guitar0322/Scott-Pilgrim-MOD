#include "stdafx.h"
#include "DobermanAttackstate.h"
#include "Dobermanidlestate.h"
#include "Doberman.h"

Dobermanstate * DobermanAttackstate::Update(Doberman * doberman)
{
	_attackTime += TIMEMANAGER->getElapsedTime();
	if (_attackTime >= 2.0f)
	{
		return new Dobermanidlestate();
	}

	return nullptr;
}

void DobermanAttackstate::Enter(Doberman * doberman)
{
	_attackTime = 0;
	if (doberman->GetDir() == false)
	{
		doberman->ChangeClip("attackRight", true);
	}
	else
	{
		doberman->ChangeClip("attackLeft", true);
	}

}

void DobermanAttackstate::Exit(Doberman * doberman)
{
}
