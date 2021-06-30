#pragma once
#include "MatthewState.h"
class MatthewPhaseSpotlightState :
	public Matthewstate
{
private:
	float _spotLightTime;
	
public:
	virtual Matthewstate* Update(Matthew* matthew);
	virtual void Enter(Matthew* matthew);
	virtual void Exit(Matthew* matthew);
};

