#pragma once
#include "SuccubusState.h"
class SuccubusIdle : public SuccubusState
{
public:
	virtual SuccubusState* Update(Succubus* succubus);
	virtual void Enter(Succubus* succubus);
	virtual void Exit(Succubus* succubus);
};

