#pragma once
#include "Matthewstate.h"
class Matthewattack3state :
	public Matthewstate
{
private:
	float _attackTime3;
public:
	virtual Matthewstate* Update(Matthew* matthew);
	virtual void Enter(Matthew* matthew);
	virtual void Exit(Matthew* matthew);
};

