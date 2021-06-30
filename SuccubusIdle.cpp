#include "stdafx.h"
#include "SuccubusIdle.h"
#include "Succubus.h"

SuccubusState * SuccubusIdle::Update(Succubus * succubus)
{
	return nullptr;
}

void SuccubusIdle::Enter(Succubus * succubus)
{
	succubus->ChangeClip("succubus_idle", true);
}

void SuccubusIdle::Exit(Succubus * succubus)
{
}
