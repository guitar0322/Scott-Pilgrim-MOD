#pragma once
#include "Dobermanstate.h"
class Dobermanidlestate :
	public Dobermanstate
{
public:
	virtual Dobermanstate* Update(Doberman* doberman);
	virtual void Enter(Doberman* doberman);
	virtual void Exit(Doberman* doberman);
};

