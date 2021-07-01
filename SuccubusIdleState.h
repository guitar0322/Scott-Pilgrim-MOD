#pragma once
#include "SuccubusState.h"
class SuccubusIdleState : public SuccubusState
{
public:
	virtual SuccubusState* Update(Succubus* succubus);
	virtual void Enter(Succubus* succubus);
	virtual void Exit(Succubus* succubus);
};

