#include "stdafx.h"
#include "MatthewAttack2State.h"
#include "MatthewAttack3State.h"
#include "MatthewAttackState.h"
#include "MatthewIdleState.h"
#include "Matthew.h"

Matthewstate * MatthewAttack2State::Update(Matthew * matthew)
{
	if (matthew->animator->GetEnd()==true)
	{
		if (matthew->_attackTime == 5)
		{
			matthew->_attackTime = 0;
			return new MatthewIdleState();
		}

		switch (RND->getInt(2))
		{
		case 0:
			return new MatthewAttackState();
			break;
		case 1:
			return new MatthewAttack3State();
			break;
		}
	}

	return nullptr;
}

void MatthewAttack2State::Enter(Matthew * matthew)
{
	matthew->_attackTime++;
	if (matthew->Getdir() == false)
	{
		matthew->ChangeCilp("matthew_attack2_right", true);
	}
	else
	{
		matthew->ChangeCilp("matthew_attack2_left", true);
	}
}

void MatthewAttack2State::Exit(Matthew * matthew)
{
}
