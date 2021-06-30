#include "stdafx.h"
#include "MatthewBlockState.h"
#include "MatthewIdleState.h"
#include "Matthew.h"

Matthewstate * MatthewBlockState::Update(Matthew * matthew)
{
	_blockTime += TIMEMANAGER->getElapsedTime();
	if (_blockTime >= 2.0f)
	{
		return new MatthewIdleState();
	}


	return nullptr;
}

void MatthewBlockState::Enter(Matthew * matthew)
{
	_blockTime = 0;
	if (matthew->Getdir() == false)
	{
		matthew->ChangeCilp("matthew_block_right", true);
	}
	else
	{
		matthew->ChangeCilp("matthew_block_left", true);
	}

}

void MatthewBlockState::Exit(Matthew * matthew)
{
}
