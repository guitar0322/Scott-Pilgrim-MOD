#include "stdafx.h"
#include "SuccubusSummonState.h"
#include "SuccubusIdle.h"
#include "Succubus.h"
#include "SuccubusIdle.h"

SuccubusState * SuccubusSummonState::Update(Succubus * succubus)
{
	if (succubus->animator->GetEnd()==true)
	{
		return new SuccubusIdle();
	}
	return nullptr;
}

void SuccubusSummonState::Enter(Succubus * succubus)
{
	succubus->ChangeClip("summon_succubus", true);
}

void SuccubusSummonState::Exit(Succubus * succubus)
{
}
