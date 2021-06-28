#include "stdafx.h"
#include "Dobermanmovestate.h"
#include "Dobermanidlestate.h"
#include "Doberman.h"

Dobermanstate * Dobermanmovestate::Update(Doberman * doberman)
{
	if (doberman->transform->GetX() < doberman->GetPlayer()->GetX())
	{
		if (doberman->GetDir()==true)
		{
			doberman->ChangeClip("moveRight", false);
			doberman->SetDir(false);
		}
	}
	else
	{
		if (doberman->GetDir() ==false)
		{
			doberman->ChangeClip("moveLeft", false);
			doberman->SetDir(true);
		}
	}
	if (GetDistance(doberman->transform->GetX(),doberman->transform->GetY(),
		doberman->GetPlayer()->GetX(),doberman->GetPlayer()->GetY())>300) // idle�� ���� �Ÿ��� ���ƾ��� �ٸ��� �����ϸ� ���� ǥ���� �ݰ涧���� �����Ÿ�.
	{
		return new Dobermanidlestate();
	}
	float Angle = GetAngle(doberman->transform->GetX(), doberman->transform->GetY(), doberman->GetPlayer()->GetX(), doberman->GetPlayer()->GetY());
	doberman->transform->Move(doberman->GetSpeed()*TIMEMANAGER->getElapsedTime()*cosf(Angle),
		doberman->GetSpeed()*TIMEMANAGER->getElapsedTime()*-sinf(Angle));


	return nullptr;
}

void Dobermanmovestate::Enter(Doberman * doberman)
{
	if (doberman->GetDir() == false)
	{
		doberman->ChangeClip("moveRight", true);
	}
	else
	{
		doberman->ChangeClip("moveLeft", true);
	}
}

void Dobermanmovestate::Exit(Doberman * doberman)
{
}
