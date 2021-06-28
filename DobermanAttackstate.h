#pragma once
#include "Dobermanstate.h"
class DobermanAttackstate :
	public Dobermanstate
{
private:
	float _attackTime;
public:
	virtual Dobermanstate* Update(Doberman* doberman);
	virtual void Enter(Doberman* doberman);
	virtual void Exit(Doberman* doberman);
};

