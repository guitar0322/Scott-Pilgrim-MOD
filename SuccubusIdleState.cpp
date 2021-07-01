#include "stdafx.h"
#include "SuccubusIdleState.h"
#include "Succubus.h"

SuccubusState * SuccubusIdleState::Update(Succubus * succubus)
{
	float angle;



	return nullptr;
}

void SuccubusIdleState::Enter(Succubus * succubus)
{
	succubus->ChangeClip("succubus_idle", true);
}

void SuccubusIdleState::Exit(Succubus * succubus)
{
}
