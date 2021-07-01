#include "stdafx.h"
#include "SuccubusIdleState.h"
#include "Succubus.h"

SuccubusState * SuccubusIdleState::Update(Succubus * succubus)
{
	_angle += 0.10f;
	succubus->transform->Move(succubus->GetSpeed()*TIMEMANAGER->getElapsedTime()*cosf(_angle), 
							  succubus->GetSpeed()*TIMEMANAGER->getElapsedTime()*-sinf(_angle));
	return nullptr;
}

void SuccubusIdleState::Enter(Succubus * succubus)
{
	_angle = PI / 4;
	succubus->ChangeClip("succubus_idle", true);
}

void SuccubusIdleState::Exit(Succubus * succubus)
{
}
