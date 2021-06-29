#pragma once
#include "Matthewstate.h"
class MatthewPalmwindState :
	public Matthewstate
{
private:
	float _palmwindtime;

public:
	virtual Matthewstate* Update(Matthew* matthew);
	virtual void Enter(Matthew* matthew);
	virtual void Exit(Matthew* matthew);
};

