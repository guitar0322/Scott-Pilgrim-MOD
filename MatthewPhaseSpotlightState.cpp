#include "stdafx.h"
#include "MatthewPhaseSpotlightState.h"
#include "MatthewPhaseEndState.h"
#include "Matthew.h"
#include "Succubus.h"

Matthewstate * MatthewPhaseSpotlightState::Update(Matthew * matthew)
{
	_spotLightTime += TIMEMANAGER->getElapsedTime();
	if (_spotLightTime >= 10.0f)
	{
		for (int i = 0; i < SUCCUBUSMAX; i++)
		{
			matthew->_succubus[i]->SetActive(false);
		}
		return new MatthewPhaseEndState();
	}

	return nullptr;
}

void MatthewPhaseSpotlightState::Enter(Matthew * matthew)
{

	for (int i = 0; i < SUCCUBUSMAX; i++)
	{
		matthew->_succubus[i]->SetActive(true); 
		matthew->_succubus[i]->GetComponent<Succubus>()->Init(); // 페이즈 종료 후에도 서큐버스 소환 페이즈부터 하려면 초기화부분도 시작해야함.
	}
	matthew->_succubus[0]->transform->SetPosition(matthew->transform->GetX() + 100, matthew->transform->GetY()-300);
	matthew->_succubus[1]->transform->SetPosition(matthew->transform->GetX() - 100, matthew->transform->GetY()-300);
	matthew->_succubus[2]->transform->SetPosition(matthew->transform->GetX()-100, matthew->transform->GetY()-100);
	matthew->_succubus[3]->transform->SetPosition(matthew->transform->GetX()+100, matthew->transform->GetY()-100);

	_spotLightTime = 0;
	if (matthew->Getdir() == false)
	{
		matthew->transform->MoveY(-150);
		matthew->ChangeCilp("matthew_phase_spotlight_right",true);
	}
	else
	{
		matthew->transform->MoveY(-150);
		matthew->ChangeCilp("matthew_phase_spotlight_left", true);
	}

}

void MatthewPhaseSpotlightState::Exit(Matthew * matthew)
{
}
