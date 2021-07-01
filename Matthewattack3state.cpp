#include "stdafx.h"
#include "MatthewAttack3State.h"
#include "MatthewAttack2State.h"
#include "MatthewAttackState.h"
#include "MatthewIdleState.h"
#include "MatthewPalmwindState.h"
#include "Matthew.h"

Matthewstate * MatthewAttack3State::Update(Matthew * matthew)
{
	if (matthew->animator->GetEnd() == true)
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
			return new MatthewAttack2State();
			break;
		}
		/*return new MatthewPalmwindState;*/
	}
	//if (_attackTime3 >= 2.0f)
	//{
	//	return new MatthewIdleState;
	//}
	return nullptr;
}

void MatthewAttack3State::Enter(Matthew * matthew)
{
	_attackTime3 = 0;
	matthew->_attackTime++;
	if (matthew->Getdir()==false)
	{
		matthew->ChangeCilp("matthew_attack3_right", true);
	}
	else
	{
		matthew->ChangeCilp("matthew_attack3_left", true);
	}
}

void MatthewAttack3State::Exit(Matthew * matthew)
{
}
