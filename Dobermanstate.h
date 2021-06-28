#pragma once
class Doberman;
class Dobermanstate
{
public:
	virtual Dobermanstate* Update(Doberman* doberman) = 0;
	virtual void Enter(Doberman* doberman) = 0;
	virtual void Exit(Doberman* doberman) = 0;
};

